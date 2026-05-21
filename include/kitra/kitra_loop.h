#ifndef KITRA_LOOP_H_
#define KITRA_LOOP_H_

#include <stdbool.h>

/**
 * @brief Returns whether the main loop should continue running.
 *
 * Typically used as the condition of the main game loop. Returns false
 * after KitraQuit() is called or the window is closed by the user.
 *
 * @return True if the loop is running, false if it should exit.
 *
 * @code
 * while (KitraIsRunning())
 * {
 *     KitraBeginFrame();
 *     // ...
 *     KitraEndFrame();
 * }
 * @endcode
 *
 * @see KitraBeginFrame(), KitraEndFrame()
 */
bool KitraIsRunning(void);

/**
 * @brief Requests the main loop to stop after the current frame.
 *
 * Sets the running flag to false, causing KitraIsRunning() to return
 * false on the next check. Does not immediately stop execution —
 * the current frame completes normally before the loop exits.
 *
 * @see KitraIsRunning(), KitraQuit()
 */
void KitraRequestQuit(void);

/**
 * @brief Begins a new frame.
 *
 * Must be called once at the start of every iteration of the main loop,
 * before any drawing or input queries. Performs the following in order:
 *
 * -# Updates delta time and smoothed FPS using an exponential moving average.
 * -# Resets per-frame input state (pressed, released, mouse delta, scroll).
 * -# Processes all pending SDL2 events, triggering KitraRequestQuit()
 *    on a window close event.
 *
 * @note Calling input functions or draw functions before KitraBeginFrame()
 *       will produce stale or undefined results.
 *
 * @see KitraEndFrame(), KitraIsRunning(), KitraGetDeltaTime()
 */
void KitraBeginFrame(void);

/**
 * @brief Ends the current frame and presents the rendered output.
 *
 * Must be called once at the end of every iteration of the main loop,
 * after all drawing is complete. Performs the following in order:
 *
 * -# If a target FPS is set, sleeps for the remaining frame time to
 *    cap the frame rate.
 * -# Presents the renderer's back buffer to the screen.
 *
 * Logs a warning and returns early if called without a matching
 * KitraBeginFrame(), or if the renderer is NULL.
 *
 * @see KitraBeginFrame(), KitraSetTargetFPS()
 */
void KitraEndFrame(void);

#endif /* KITRA_LOOP_H_ */