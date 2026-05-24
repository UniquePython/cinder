#ifndef KITRA_TIMER_H_
#define KITRA_TIMER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

    /**
     * @brief State for a high-resolution timer.
     *
     * Tracks elapsed time using the performance counter, with support for
     * repeat firing and pausing. Initialise with @p KitraStartTimer and
     * interact via the timer API rather than accessing fields directly.
     *
     * @see KitraStartTimer, KitraResetTimer, KitraTimerDone, KitraPauseTimer
     */
    typedef struct KitraTimer
    {
        uint64_t start;    /**< Performance counter value at the time the timer was started or last reset. */
        uint64_t last;     /**< Performance counter value at the last repeat tick, used by @p KitraTimerDone. */
        uint64_t pausedAt; /**< Performance counter value at the moment the timer was paused. */
        bool repeat;       /**< If @p true, the timer fires repeatedly at each interval rather than once. */
        bool paused;       /**< If @p true, the timer is currently paused and not advancing. */

    } KitraTimer;

    /**
     * @brief Creates and starts a new timer.
     *
     * Captures the current performance counter as both the start and last
     * tick, with repeat mode disabled.
     *
     * @return  A freshly started @p KitraTimer.
     *
     * @see KitraResetTimer, KitraGetTimerElapsed, KitraTimerDone
     */
    KitraTimer KitraStartTimer(void);

    /**
     * @brief Resets a timer back to the current moment.
     *
     * Updates both the start and last tick to now, effectively restarting
     * the timer without changing its repeat setting. Does nothing if @p t
     * is @p NULL.
     *
     * @param t  Timer to reset.
     *
     * @see KitraStartTimer, KitraGetTimerElapsed
     */
    void KitraResetTimer(KitraTimer *t);

    /**
     * @brief Returns the total elapsed time since the timer was started or reset.
     *
     * @param t  Timer to query.
     * @return   Seconds elapsed since @p t was started or last reset, or
     *           @p 0.0f if @p t is @p NULL.
     *
     * @see KitraStartTimer, KitraResetTimer, KitraTimerDone
     */
    float KitraGetTimerElapsed(const KitraTimer *t);

    /**
     * @brief Pauses a timer, freezing elapsed time.
     *
     * Has no effect if @p t is NULL or already paused.
     *
     * @param t  Timer to pause.
     *
     * @see KitraTimerResume, KitraTimerDone
     */
    void KitraTimerPause(KitraTimer *t);

    /**
     * @brief Resumes a paused timer.
     *
     * Has no effect if @p t is NULL or not paused.
     *
     * @param t  Timer to resume.
     *
     * @see KitraTimerPause
     */
    void KitraTimerResume(KitraTimer *t);

    /**
     * @brief Returns the time remaining until a timer reaches @p duration.
     *
     * Returns 0.0f if the timer has already expired or @p t is NULL.
     *
     * @param t         Timer to query.
     * @param duration  Target duration in seconds.
     * @return          Seconds remaining, or 0.0f if already elapsed.
     *
     * @see KitraGetTimerElapsed, KitraTimerDone
     */
    float KitraGetTimerRemaining(const KitraTimer *t, float duration);

    /**
     * @brief Returns whether a timer has reached the given duration.
     *
     * Checks whether at least @p duration seconds have elapsed since the timer's
     * last tick. If repeat mode is enabled, the last tick is advanced by
     * @p duration on expiry rather than reset to now, preserving sub-frame
     * accuracy for fixed-interval callbacks. Does nothing and returns @p false
     * if @p t is @p NULL.
     *
     * @param t         Timer to check.
     * @param duration  Duration threshold in seconds.
     * @return          @p true if @p duration seconds have elapsed since the
     *                  last tick, @p false otherwise.
     *
     * @see KitraTimerSetRepeat, KitraGetTimerElapsed
     */
    bool KitraTimerDone(KitraTimer *t, float duration);

    /**
     * @brief Sets whether a timer automatically repeats.
     *
     * When repeat mode is enabled, @p KitraTimerDone advances the internal
     * last-tick timestamp on expiry rather than requiring a manual reset,
     * making it suitable for fixed-interval callbacks. Does nothing if @p t
     * is @p NULL.
     *
     * @param t       Timer to modify.
     * @param repeat  If @p true, the timer repeats; if @p false, it fires once.
     *
     * @see KitraTimerDone
     */
    void KitraTimerSetRepeat(KitraTimer *t, bool repeat);

    /**
     * @brief Returns the duration of the last frame in seconds.
     *
     * Useful for frame-rate-independent movement and animation. Updated once
     * per frame by the engine's main loop.
     *
     * @return  Delta time of the last frame in seconds.
     *
     * @see KitraSetTargetFPS, KitraGetFPS
     */
    float KitraGetDeltaTime(void);

    /**
     * @brief Sets the target frame rate of the engine's main loop.
     *
     * The engine will attempt to cap the frame rate at @p fps by sleeping at
     * the end of each frame. Pass @p 0 to disable the cap and run unconstrained.
     *
     * @param fps  Desired frame rate in frames per second.
     *
     * @see KitraGetFPS, KitraGetDeltaTime
     */
    void KitraSetTargetFPS(int fps);

    /**
     * @brief Returns the target frame rate set by KitraSetTargetFPS.
     *
     * Returns 0 if no cap is set.
     *
     * @return  Target FPS, or 0 if uncapped.
     *
     * @see KitraSetTargetFPS, KitraGetFPS
     */
    int KitraGetTargetFPS(void);

    /**
     * @brief Returns the current measured frame rate.
     *
     * @return  Frames per second as measured over recent frames.
     *
     * @see KitraSetTargetFPS, KitraGetDeltaTime
     */
    float KitraGetFPS(void);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_TIMER_H_ */