#ifndef KITRA_AUDIO_H_
#define KITRA_AUDIO_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

    typedef struct KitraSound KitraSound;
    typedef struct KitraMusic KitraMusic;

    /**
     * @brief Loads a sound effect from a WAV file.
     *
     * Allocates and returns a new @p KitraSound backed by the given WAV file.
     * The audio subsystem must have been initialized via @p KITRA_SUBSYSTEM_AUDIO
     * passed to @p KitraInit before calling this function.
     *
     * @param path  Path to the WAV file to load.
     * @return      Pointer to a newly allocated @p KitraSound on success, or
     *              @p NULL if the audio subsystem is not initialized, the file
     *              could not be loaded, or memory allocation failed.
     *
     * @note The caller is responsible for freeing the returned sound with
     *       @p KitraFreeSound (or equivalent) when it is no longer needed.
     *
     * @see KitraInit, KitraFreeSound
     */
    KitraSound *KitraLoadSound(const char *path);

    /**
     * @brief Destroys a sound effect and releases all associated resources.
     *
     * Frees the underlying @p Mix_Chunk and the @p KitraSound allocation, then
     * sets the caller's pointer to @p NULL to prevent dangling references. Safe
     * to call with @p NULL or a pointer to @p NULL.
     *
     * @param sound  Address of the @p KitraSound pointer to destroy.
     *
     * @see KitraLoadSound
     */
    void KitraDestroySound(KitraSound **sound);

    /**
     * @brief Plays a sound effect on any available channel.
     *
     * Plays @p sound once on the first available mixing channel. If no channel
     * is free the call is silently ignored by the underlying mixer. Does nothing
     * if @p sound is @p NULL.
     *
     * @param sound  Sound to play.
     *
     * @see KitraSetSoundVolume
     */
    void KitraPlaySound(KitraSound *sound);

    /**
     * @brief Stops a currently playing sound effect.
     *
     * Halts playback of @p sound on the channel it was last played on.
     * Has no effect if @p sound is @p NULL or has never been played.
     *
     * @param sound  Sound to stop.
     *
     * @see KitraPlaySound, KitraPlaySoundVolume
     */
    void KitraStopSound(KitraSound *sound);

    /**
     * @brief Sets the playback volume of a sound effect.
     *
     * @p volume is clamped to [0.0, 1.0] and mapped to the mixer's internal
     * volume range before being applied. Does nothing if @p sound is @p NULL.
     *
     * @param sound   Sound to adjust.
     * @param volume  Desired volume in the range [0.0, 1.0], where 0.0 is
     *                silent and 1.0 is full volume.
     *
     * @see KitraPlaySound
     */
    void KitraSetSoundVolume(KitraSound *sound, float volume);

    /**
     * @brief Plays a sound effect at a temporary volume.
     *
     * Plays @p sound once at @p volume without permanently changing the
     * sound's volume. The original volume is restored after playback begins.
     *
     * @param sound   Sound to play.
     * @param volume  Temporary volume in the range [0.0, 1.0].
     *
     * @see KitraPlaySound, KitraSetSoundVolume
     */
    void KitraPlaySoundVolume(KitraSound *sound, float volume);

    /**
     * @brief Sets the volume for all currently active sound channels.
     *
     * Applies @p volume globally to all open mixer channels. Does not
     * affect the stored volume of individual sounds, and does not apply
     * to sounds played in the future.
     *
     * @param volume  Desired volume in the range [0.0, 1.0].
     *
     * @see KitraSetSoundVolume, KitraSetMusicVolume
     */
    void KitraSetMasterSoundVolume(float volume);

    /**
     * @brief Loads a music track from a file.
     *
     * Allocates and returns a new @p KitraMusic backed by the given file.
     * Unlike sound effects, music is streamed rather than loaded entirely into
     * memory, making this suitable for longer tracks. The audio subsystem must
     * have been initialized via @p KITRA_SUBSYSTEM_AUDIO passed to @p KitraInit
     * before calling this function.
     *
     * @param path  Path to the music file to load.
     * @return      Pointer to a newly allocated @p KitraMusic on success, or
     *              @p NULL if the audio subsystem is not initialized, the file
     *              could not be loaded, or memory allocation failed.
     *
     * @note The caller is responsible for freeing the returned music with
     *       @p KitraDestroyMusic when it is no longer needed.
     *
     * @see KitraInit, KitraDestroyMusic, KitraLoadSound
     */
    KitraMusic *KitraLoadMusic(const char *path);

    /**
     * @brief Destroys a music track and releases all associated resources.
     *
     * Frees the underlying @p Mix_Music handle and the @p KitraMusic allocation,
     * then sets the caller's pointer to @p NULL to prevent dangling references.
     * Safe to call with @p NULL or a pointer to @p NULL.
     *
     * @param music  Address of the @p KitraMusic pointer to destroy.
     *
     * @see KitraLoadMusic
     */
    void KitraDestroyMusic(KitraMusic **music);

    /**
     * @brief Plays a music track, optionally looping.
     *
     * Begins playback of @p music from the start. Only one music track may play
     * at a time — calling this while another track is playing will replace it.
     * Does nothing if @p music is @p NULL.
     *
     * @param music  Music track to play.
     * @param loop   If @p true, the track loops indefinitely until stopped;
     *               if @p false, it plays once and stops.
     *
     * @see KitraStopMusic, KitraPauseMusic, KitraSetMusicVolume
     */
    void KitraPlayMusic(KitraMusic *music, bool loop);

    /**
     * @brief Stops music playback immediately.
     *
     * Halts the currently playing music track. Has no effect if no music
     * is playing.
     *
     * @see KitraPlayMusic, KitraPauseMusic
     */
    void KitraStopMusic(void);

    /**
     * @brief Pauses the currently playing music track.
     *
     * Pauses playback without resetting the position, allowing it to be resumed
     * from the same point. Has no effect if no music is playing or if music is
     * already paused.
     *
     * @see KitraResumeMusic, KitraStopMusic
     */
    void KitraPauseMusic(void);

    /**
     * @brief Resumes a paused music track.
     *
     * Continues playback from the position at which the track was paused.
     * Has no effect if the music is not paused.
     *
     * @see KitraPauseMusic, KitraPlayMusic
     */
    void KitraResumeMusic(void);

    /**
     * @brief Returns whether music is currently playing.
     *
     * @return @p true if a music track is actively playing and not paused,
     *         @p false otherwise.
     *
     * @see KitraPlayMusic, KitraPauseMusic
     */
    bool KitraIsMusicPlaying(void);

    /**
     * @brief Returns whether music is currently paused.
     *
     * @return @p true if a music track is paused, @p false otherwise.
     *
     * @see KitraPauseMusic, KitraResumeMusic, KitraIsMusicPlaying
     */
    bool KitraIsMusicPaused(void);

    /**
     * @brief Sets the global music playback volume.
     *
     * @p volume is clamped to [0.0, 1.0] and mapped to the mixer's internal
     * volume range before being applied. Affects all music playback globally
     * rather than a specific track.
     *
     * @param volume  Desired volume in the range [0.0, 1.0], where 0.0 is
     *                silent and 1.0 is full volume.
     *
     * @see KitraPlayMusic, KitraSetSoundVolume
     */
    void KitraSetMusicVolume(float volume);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_AUDIO_H_ */