#ifndef KITRA_PLUGIN_H_
#define KITRA_PLUGIN_H_

#include "kitra_status.h"

#include <stdint.h>

/**
 * @brief Maximum number of plugins that can be registered with the engine.
 *
 * Caps the size of the internal plugin registry. Can be overridden by
 * defining @p KITRA_MAX_PLUGINS before including the Kitra header.
 *
 * @see KitraRegisterPlugin
 */
#ifndef KITRA_MAX_PLUGINS
#define KITRA_MAX_PLUGINS 16
#endif

/**
 * @brief Opaque handle identifying a registered plugin.
 *
 * Returned by @p KitraRegisterPlugin and used for all subsequent operations
 * on the plugin. The @p index field addresses a stable indirection slot —
 * not a position in the dense plugin array — so handles remain valid
 * regardless of other plugins being registered or unregistered. The
 * @p generation field detects use-after-unregister: once a plugin is removed
 * its slot's generation is incremented, making all prior copies of the handle
 * permanently stale.
 *
 * Use @p KITRA_PLUGIN_HANDLE_INVALID as a safe null/sentinel value, and
 * @p KitraPluginHandleIsValid to check whether a handle has been initialized
 * before passing it to the API.
 *
 * @see KitraRegisterPlugin, KitraUnregisterPlugin, KitraPluginHandleIsValid,
 *      KITRA_PLUGIN_HANDLE_INVALID
 */
typedef struct KitraPluginHandle
{
    uint16_t index;      /**< Index into the sparse indirection table. */
    uint16_t generation; /**< Generation of the slot at the time of registration. */
} KitraPluginHandle;

/**
 * @brief Sentinel value representing an invalid or unset plugin handle.
 *
 * @see KitraPluginHandleIsValid
 */
#define KITRA_PLUGIN_HANDLE_INVALID ((KitraPluginHandle){UINT16_MAX, UINT16_MAX})

/**
 * @brief Returns true if @p handle is not the sentinel invalid value.
 *
 * This is a structural check only — it does not verify that the referenced
 * slot is still occupied. A handle that passes this check may still be stale
 * if the plugin has been unregistered; the API functions perform the full
 * generation check internally.
 *
 * @param handle  Handle to test.
 *
 * @see KITRA_PLUGIN_HANDLE_INVALID
 */
#define KitraPluginHandleIsValid(handle) \
    ((handle).index != UINT16_MAX || (handle).generation != UINT16_MAX)

/**
 * @brief Descriptor for a Kitra engine plugin.
 *
 * Bundles a plugin's name, lifecycle callbacks, and userdata into a single
 * struct passed to @p KitraRegisterPlugin. Any callback may be @p NULL if
 * that lifecycle stage is not needed by the plugin.
 *
 * @see KitraRegisterPlugin, KITRA_MAX_PLUGINS
 */
typedef struct KitraPlugin
{
    const char *name;                         /**< Human-readable plugin name, used for logging. May be @p NULL. */
    void (*init)(void *userdata);             /**< Called once when the plugin is registered. May be @p NULL. */
    void (*update)(float dt, void *userdata); /**< Called every frame with the delta time in seconds. May be @p NULL. */
    void (*draw)(void *userdata);             /**< Called every frame during the draw stage. May be @p NULL. */
    void (*shutdown)(void *userdata);         /**< Called once when the plugin is unregistered. May be @p NULL. */
    void *userdata;                           /**< Arbitrary pointer passed to every callback. May be @p NULL. */
} KitraPlugin;

/**
 * @brief Registers a plugin with the engine.
 *
 * Finds a free slot in the indirection table, stores @p plugin in the dense
 * array, then immediately invokes its @p init callback if one is provided.
 * The plugin is subsequently ticked each frame in the order it appears in the
 * dense array.
 *
 * On success, a valid @p KitraPluginHandle is returned and, if @p status is
 * non-NULL, @p *status is set to @p KITRA_STATUS_OK. On failure,
 * @p KITRA_PLUGIN_HANDLE_INVALID is returned and @p *status (if non-NULL)
 * is set to the relevant error code.
 *
 * @param plugin   Plugin descriptor to register.
 * @param status   Optional out-parameter for the status code. May be @p NULL.
 * @return         A valid @p KitraPluginHandle on success, or
 *                 @p KITRA_PLUGIN_HANDLE_INVALID if the registry is full
 *                 (@p KITRA_STATUS_PLUGIN_MAX_REACHED written to @p *status).
 *
 * @see KitraUnregisterPlugin, KitraPlugin, KITRA_MAX_PLUGINS,
 *      KitraPluginHandleIsValid, KITRA_PLUGIN_HANDLE_INVALID
 */
KitraPluginHandle KitraRegisterPlugin(KitraPlugin plugin, KitraStatus *status);

/**
 * @brief Unregisters a plugin by handle and invokes its shutdown callback.
 *
 * Validates @p handle against the current generation of the referenced slot.
 * If valid, calls the plugin's @p shutdown callback (if set), removes it from
 * the dense array via an O(1) swap-with-last, and recycles the slot back onto
 * the free list. The slot's generation is incremented, permanently invalidating
 * all existing copies of @p handle. All other plugin handles are unaffected.
 *
 * @param handle  Handle returned by @p KitraRegisterPlugin.
 * @return        @p KITRA_STATUS_OK on success, or
 *                @p KITRA_STATUS_PLUGIN_INVALID_HANDLE if @p handle is stale
 *                or was never returned by @p KitraRegisterPlugin.
 *
 * @see KitraRegisterPlugin, KitraPlugin
 */
KitraStatus KitraUnregisterPlugin(KitraPluginHandle handle);

#endif /* KITRA_PLUGIN_H_ */