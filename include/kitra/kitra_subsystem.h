#ifndef KITRA_SUBSYSTEM_H_
#define KITRA_SUBSYSTEM_H_

#include "kitra_status.h"

/**
 * @brief Flags for selecting which Kitra subsystems to initialize.
 *
 * Pass one or more of these flags to KitraInit(), combined with the
 * bitwise OR operator. Use KITRA_SUBSYSTEM_ALL to initialize everything.
 *
 * @code
 * KitraInit(KITRA_SUBSYSTEM_VIDEO | KITRA_SUBSYSTEM_AUDIO);
 * @endcode
 *
 * @see KitraInit()
 */
typedef enum
{
    KITRA_SUBSYSTEM_NONE = 0,                                                                     /**< No subsystems. */
    KITRA_SUBSYSTEM_EVENTS = 1u << 0,                                                             /**< Event processing — required for input handling. */
    KITRA_SUBSYSTEM_AUDIO = 1u << 1,                                                              /**< Audio — required for sound effects and music. */
    KITRA_SUBSYSTEM_VIDEO = 1u << 2,                                                              /**< Video — required for window creation and rendering. */
    KITRA_SUBSYSTEM_ALL = KITRA_SUBSYSTEM_EVENTS | KITRA_SUBSYSTEM_AUDIO | KITRA_SUBSYSTEM_VIDEO, /**< All subsystems. */

} KitraSubsystem;

/**
 * @brief Initializes the Kitra library and the requested subsystems.
 *
 * Must be called once before any other Kitra function. Initializes
 * SDL2 subsystems based on the provided flags, seeds the global RNG,
 * and sets up the default log callback. Subsystems are initialized in
 * dependency order with rollback safety — if any subsystem fails, all
 * previously initialized subsystems are cleanly shut down before returning.
 *
 * @param flags One or more @ref KitraSubsystem flags combined with
 *              the bitwise OR operator. Use KITRA_SUBSYSTEM_ALL to
 *              initialize everything.
 *
 * @return KITRA_STATUS_OK on success.
 * @return KITRA_STATUS_SUBSYSTEM_DOUBLE_INIT if KitraInit() has
 *         already been called without a matching KitraQuit().
 * @return KITRA_STATUS_SUBSYSTEM_INIT_FAILED if any SDL2 subsystem
 *         or SDL2_mixer failed to initialize.
 *
 * @see KitraQuit(), KitraSubsystem
 */
KitraStatus KitraInit(KitraSubsystem flags);

/**
 * @brief Shuts down the Kitra library and frees all resources.
 *
 * Shuts down all active subsystems and releases all resources in the
 * correct order — the window, renderer, and SDL2 subsystems. Should be
 * called once at the end of the program, after the main loop exits.
 *
 * @note Calling any Kitra function after KitraQuit() results in
 *       undefined behavior unless KitraInit() is called again first.
 *
 * @see KitraInit()
 */
void KitraQuit(void);

#endif /* KITRA_SUBSYSTEM_H_ */