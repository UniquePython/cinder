#ifndef KITRA_INTERNAL_H_
#define KITRA_INTERNAL_H_

#define _POSIX_C_SOURCE 200809L

#include "kitra/kitra.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Internal state of the Kitra library.
 *
 * Holds the core SDL2 objects and initialization flags used throughout
 * the library. This struct is managed internally by Kitra — do not
 * create or modify it directly.
 *
 * @note Access the window and renderer via KitraGetWindow() and
 *       KitraGetRenderer() if you need them for advanced SDL2 usage.
 */
typedef struct KitraCoreState
{
    SDL_Window *window;     /**< The SDL2 window handle. */
    SDL_Renderer *renderer; /**< The SDL2 renderer handle. */
    uint32_t initFlags;     /**< SDL subsystem flags passed to KitraInit(). */
    bool imgInitialized;    /**< Whether SDL2_image was successfully initialized. */
    bool ttfInitialized;    /**< Whether SDL2_ttf was successfully initialized. */
    bool audioInitialized;  /**< Whether SDL2_mixer was successfully initialized. */
} KitraCoreState;

/**
 * @brief Internal state of the Kitra game loop.
 *
 * Tracks the current frame and loop lifecycle. Managed internally —
 * do not create or modify it directly.
 */
typedef struct KitraLoopState
{
    bool isRunning;  /**< Whether the main loop is currently running. Set to false by KitraQuit(). */
    bool frameBegun; /**< Whether KitraBeginFrame() has been called without a matching KitraEndFrame(). */
    bool resized;    /**< Whether the window was resized this frame. */
} KitraLoopState;

/**
 * @brief Internal timing state used to track frame timing and FPS.
 *
 * Manages delta time, FPS calculation, and optional FPS capping.
 * Managed internally — do not create or modify it directly.
 */
typedef struct KitraTimingState
{
    uint64_t perfFrequency; /**< SDL2 performance counter frequency, used for high-resolution timing. */
    uint64_t lastCounter;   /**< Performance counter value at the start of the last frame. */
    float deltaTime;        /**< Time in seconds elapsed since the last frame. */
    float fps;              /**< Current frames per second, updated each frame. */
    int targetFPS;          /**< Target FPS cap. Set to 0 to disable frame rate limiting. */
} KitraTimingState;

/**
 * @brief Internal keyboard input state for the current frame.
 *
 * Tracks the per-frame state of every key. Updated at the start of
 * each frame by KitraBeginFrame(). Managed internally — do not
 * create or modify it directly.
 *
 * @see KitraIsKeyDown(), KitraIsKeyPressed(), KitraIsKeyReleased()
 */
typedef struct KitraKeyboardState
{
    bool down[KITRA_KEY_COUNT];     /**< True while the key is held down. */
    bool pressed[KITRA_KEY_COUNT];  /**< True only on the frame the key was first pressed. */
    bool released[KITRA_KEY_COUNT]; /**< True only on the frame the key was released. */
} KitraKeyboardState;

/**
 * @brief Internal mouse input state for the current frame.
 *
 * Tracks mouse position, movement, scroll, and button states.
 * Updated at the start of each frame by KitraBeginFrame().
 * Managed internally — do not create or modify it directly.
 *
 * @see KitraGetMousePos(), KitraIsMouseButtonDown(),
 *      KitraIsMouseButtonPressed(), KitraIsMouseButtonReleased()
 */
typedef struct KitraMouseState
{
    KitraPoint pos;                          /**< Current mouse position in window coordinates. */
    KitraPoint prevPos;                      /**< Mouse position during the previous frame. */
    KitraVec2i delta;                        /**< Mouse movement since the last frame. */
    KitraVec2i scrollDelta;                  /**< Scroll wheel delta this frame. */
    bool down[KITRA_MOUSE_BUTTON_COUNT];     /**< True while the button is held down. */
    bool pressed[KITRA_MOUSE_BUTTON_COUNT];  /**< True only on the frame the button was first pressed. */
    bool released[KITRA_MOUSE_BUTTON_COUNT]; /**< True only on the frame the button was released. */
} KitraMouseState;

/**
 * @brief Internal input state aggregating keyboard and mouse state.
 *
 * Combines keyboard and mouse state into a single struct. Updated at
 * the start of each frame by KitraBeginFrame(). Managed internally —
 * do not create or modify it directly.
 *
 * @see KitraKeyboardState, KitraMouseState
 */
typedef struct KitraInputState
{
    KitraKeyboardState keyboard; /**< Current keyboard input state. */
    KitraMouseState mouse;       /**< Current mouse input state. */
} KitraInputState;

/**
 * @brief Internal logging and error state.
 *
 * Tracks the user-provided log callback and the most recent error
 * message and severity. Managed internally — do not create or modify
 * it directly.
 *
 * @see KitraSetErrorCallback(), KitraGetLastError(), KitraLogLevel
 */
typedef struct KitraLogState
{
    KitraErrorCallback callback; /**< User-provided callback invoked on every log message. NULL if not set. */
    void *userdata;              /**< User-provided pointer passed through to the callback. */
    const char *lastError;       /**< The most recent error message, or NULL if no error has occurred. */
    KitraLogLevel lastLevel;     /**< Severity level of the most recent log message. */
} KitraLogState;

/**
 * @brief The global Kitra context.
 *
 * The single top-level struct that holds all library state — core SDL2
 * objects, loop control, timing, input, logging, and RNG.
 * There is exactly one instance of this struct for the lifetime of the
 * application. Managed internally — do not create or modify it directly.
 *
 * @see KitraInit(), KitraQuit()
 */
typedef struct KitraCtx
{
    KitraCoreState core;     /**< Core SDL2 window and renderer state. */
    KitraLoopState loop;     /**< Game loop lifecycle state. */
    KitraTimingState timing; /**< Frame timing, delta time and FPS state. */
    KitraInputState input;   /**< Keyboard and mouse input state. */
    KitraLogState log;       /**< Logging and error reporting state. */
    KitraRng rng;            /**< Global random number generator instance. */
} KitraCtx;

extern KitraCtx gKitraCtx;

void KitraInputInit(void);
void KitraInputProcessEvent(const SDL_Event *event);

SDL_Texture *KitraTextureGetSDL(KitraTexture *tex);
KitraTexture *KitraTextureFromSDL(SDL_Texture *tex, int w, int h);

KitraSurface *KitraSurfaceFromSDL(SDL_Surface *surface);

#endif /* KITRA_INTERNAL_H_ */