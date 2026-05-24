#ifndef KITRA_WINDOW_H_
#define KITRA_WINDOW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"
#include "kitra_status.h"

#include <stdbool.h>

    /**
     * @brief Flags controlling window creation behaviour.
     *
     * Bitmask values that can be combined with bitwise OR and passed to
     * @p KitraWindowDesc to configure the initial window state.
     *
     * @see KitraCreateWindow, KitraWindowDesc
     */
    typedef enum
    {
        KITRA_WINDOW_NONE = 0,             /**< No special window behaviour. */
        KITRA_WINDOW_SHOWN = 1u << 0,      /**< Window is visible on creation. */
        KITRA_WINDOW_RESIZABLE = 1u << 1,  /**< Window can be resized by the user. */
        KITRA_WINDOW_FULLSCREEN = 1u << 2, /**< Window starts in fullscreen mode. */
        KITRA_WINDOW_BORDERLESS = 1u << 3, /**< Window is created without a title bar or border. */
        KITRA_WINDOW_HIDDEN = 1u << 4,     /**< Window is hidden on creation. */

    } KitraWindowFlags;

    /**
     * @brief Descriptor for window creation parameters.
     *
     * Passed to @p KitraCreateWindow to configure the window. Position is specified
     * either via @p pos or by centering on one or both axes with @p centerX
     * and @p centerY; if an axis is centered, the corresponding component of
     * @p pos is ignored.
     *
     * @see KitraCreateWindow, KitraWindowFlags
     */
    typedef struct KitraWindowDesc
    {
        const char *title; /**< Window title shown in the title bar. */
        KitraSize size;    /**< Width and height of the window in pixels. */
        KitraPoint pos;    /**< Initial window position in screen coordinates. Ignored on axes where @p centerX or @p centerY is @p true. */

        bool centerX; /**< If @p true, the window is centered horizontally on the display. */
        bool centerY; /**< If @p true, the window is centered vertically on the display. */

        KitraWindowFlags flags; /**< Bitwise OR of @p KitraWindowFlags values controlling window behaviour. */

    } KitraWindowDesc;

    /**
     * @brief Returns a @p KitraWindowDesc populated with sensible defaults.
     *
     * The returned descriptor creates a 900×600 window titled "Kitra",
     * centered on the display, and initially visible and resizable.
     * Individual fields can be overridden after calling this function before
     * passing the descriptor to @p KitraCreateWindow.
     *
     * @return  A @p KitraWindowDesc with default values.
     *
     * @see KitraWindowDesc, KitraCreateWindow
     */
    KitraWindowDesc KitraDefaultWindowDesc(void);

    /**
     * @brief Creates the application window and hardware-accelerated renderer.
     *
     * Constructs an SDL window and renderer from @p winDesc, storing both in the
     * global engine context. On success the engine's main loop flag is set to
     * running. If renderer creation fails, the window is destroyed and the context
     * is cleaned up before returning.
     *
     * @param winDesc  Descriptor specifying the window's title, size, position,
     *                 and flags.
     * @return         @p KITRA_STATUS_OK on success, or one of:
     *                 - @p KITRA_STATUS_WINDOW_CREATE_FAILED if the window could
     *                   not be created.
     *                 - @p KITRA_STATUS_RENDERER_CREATE_FAILED if the
     *                   hardware-accelerated renderer could not be created.
     *
     * @see KitraDestroyWindow, KitraWindowDesc, KitraDefaultWindowDesc
     */
    KitraStatus KitraCreateWindow(KitraWindowDesc winDesc);

    /**
     * @brief Destroys the application window and renderer.
     *
     * Releases the renderer and window held in the global engine context, in that
     * order, and sets both pointers to @p NULL. Safe to call when either or both
     * have already been destroyed.
     *
     * @see KitraCreateWindow
     */
    void KitraDestroyWindow(void);

    /**
     * @brief Sets the window icon.
     *
     * Uses the pixel data of @p surface as the window icon. SDL copies
     * the data internally, so the surface may be destroyed immediately
     * after this call.
     *
     * @param surface  Surface to use as the window icon.
     *
     * @see KitraLoadSurface, KitraDestroySurface
     */
    void KitraSetWindowIcon(KitraSurface *surface);

    /**
     * @brief Returns the current size of the application window.
     *
     * Queries the window for its current dimensions, reflecting any resizes
     * that have occurred since creation.
     *
     * @return  Current window dimensions as a @p KitraSize, or a zero
     *          @p KitraSize if the window is @p NULL.
     *
     * @see KitraIsWindowResized, KitraGetWindowDesc
     */
    KitraSize KitraGetWindowSize(void);

    /**
     * @brief Returns whether the window was resized this frame.
     *
     * @return  @p true if a resize event was received this frame,
     *          @p false otherwise.
     *
     * @see KitraGetWindowSize
     */
    bool KitraIsWindowResized(void);

    /**
     * @brief Sets the window title.
     *
     * Does nothing if the window is NULL or @p title is NULL.
     *
     * @param title  Null-terminated string to display in the title bar.
     *
     * @see KitraDefaultWindowDesc
     */
    void KitraSetWindowTitle(const char *title);

    /**
     * @brief Returns the current position of the window on the display.
     *
     * @return  Top-left corner of the window in screen coordinates as a
     *          @p KitraPoint, or a zero point if the window is NULL.
     *
     * @see KitraGetWindowSize
     */
    KitraPoint KitraGetWindowPos(void);

    /**
     * @brief Resizes the window.
     *
     * Does nothing if the window is NULL.
     *
     * @param size  New window dimensions in pixels.
     *
     * @see KitraGetWindowSize
     */
    void KitraSetWindowSize(KitraSize size);

    /**
     * @brief Returns the underlying SDL window handle.
     *
     * Provides access to the raw @p SDL_Window pointer for interoperability
     * with SDL APIs not wrapped by Kitra. Ownership remains with the engine —
     * do not destroy the returned pointer directly.
     *
     * @return  The underlying @p SDL_Window pointer.
     *
     * @see KitraGetSDLRenderer
     */
    struct SDL_Window *KitraGetSDLWindow(void);

    /**
     * @brief Returns the underlying SDL renderer handle.
     *
     * Provides access to the raw @p SDL_Renderer pointer for interoperability
     * with SDL APIs not wrapped by Kitra. Ownership remains with the engine —
     * do not destroy the returned pointer directly.
     *
     * @return  The underlying @p SDL_Renderer pointer.
     *
     * @see KitraGetSDLWindow
     */
    struct SDL_Renderer *KitraGetSDLRenderer(void);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_WINDOW_H_ */