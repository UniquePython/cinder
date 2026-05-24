#ifndef KITRA_INPUT_H_
#define KITRA_INPUT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"

#include <stdbool.h>

    /**
     * @brief Keyboard key identifiers.
     *
     * Platform-independent key codes used throughout the input API. Values are
     * stable integers that can be used as array indices. @p KITRA_KEY_COUNT
     * gives the total number of tracked keys and is suitable for sizing
     * per-key arrays.
     *
     * @see KitraIsKeyDown, KitraIsKeyPressed, KitraIsKeyReleased
     */
    typedef enum KitraKey
    {
        KITRA_KEY_UNKNOWN = 0, /**< Unknown or unmapped key. */

        /* — Alphabet — */
        KITRA_KEY_A = 1,  /**< A key. */
        KITRA_KEY_B = 2,  /**< B key. */
        KITRA_KEY_C = 3,  /**< C key. */
        KITRA_KEY_D = 4,  /**< D key. */
        KITRA_KEY_E = 5,  /**< E key. */
        KITRA_KEY_F = 6,  /**< F key. */
        KITRA_KEY_G = 7,  /**< G key. */
        KITRA_KEY_H = 8,  /**< H key. */
        KITRA_KEY_I = 9,  /**< I key. */
        KITRA_KEY_J = 10, /**< J key. */
        KITRA_KEY_K = 11, /**< K key. */
        KITRA_KEY_L = 12, /**< L key. */
        KITRA_KEY_M = 13, /**< M key. */
        KITRA_KEY_N = 14, /**< N key. */
        KITRA_KEY_O = 15, /**< O key. */
        KITRA_KEY_P = 16, /**< P key. */
        KITRA_KEY_Q = 17, /**< Q key. */
        KITRA_KEY_R = 18, /**< R key. */
        KITRA_KEY_S = 19, /**< S key. */
        KITRA_KEY_T = 20, /**< T key. */
        KITRA_KEY_U = 21, /**< U key. */
        KITRA_KEY_V = 22, /**< V key. */
        KITRA_KEY_W = 23, /**< W key. */
        KITRA_KEY_X = 24, /**< X key. */
        KITRA_KEY_Y = 25, /**< Y key. */
        KITRA_KEY_Z = 26, /**< Z key. */

        /* — Digits — */
        KITRA_KEY_0 = 27, /**< 0 key. */
        KITRA_KEY_1 = 28, /**< 1 key. */
        KITRA_KEY_2 = 29, /**< 2 key. */
        KITRA_KEY_3 = 30, /**< 3 key. */
        KITRA_KEY_4 = 31, /**< 4 key. */
        KITRA_KEY_5 = 32, /**< 5 key. */
        KITRA_KEY_6 = 33, /**< 6 key. */
        KITRA_KEY_7 = 34, /**< 7 key. */
        KITRA_KEY_8 = 35, /**< 8 key. */
        KITRA_KEY_9 = 36, /**< 9 key. */

        /* — Function keys — */
        KITRA_KEY_F1 = 37,  /**< F1 key. */
        KITRA_KEY_F2 = 38,  /**< F2 key. */
        KITRA_KEY_F3 = 39,  /**< F3 key. */
        KITRA_KEY_F4 = 40,  /**< F4 key. */
        KITRA_KEY_F5 = 41,  /**< F5 key. */
        KITRA_KEY_F6 = 42,  /**< F6 key. */
        KITRA_KEY_F7 = 43,  /**< F7 key. */
        KITRA_KEY_F8 = 44,  /**< F8 key. */
        KITRA_KEY_F9 = 45,  /**< F9 key. */
        KITRA_KEY_F10 = 46, /**< F10 key. */
        KITRA_KEY_F11 = 47, /**< F11 key. */
        KITRA_KEY_F12 = 48, /**< F12 key. */

        /* — Navigation — */
        KITRA_KEY_UP = 49,       /**< Up arrow key. */
        KITRA_KEY_DOWN = 50,     /**< Down arrow key. */
        KITRA_KEY_LEFT = 51,     /**< Left arrow key. */
        KITRA_KEY_RIGHT = 52,    /**< Right arrow key. */
        KITRA_KEY_HOME = 53,     /**< Home key. */
        KITRA_KEY_END = 54,      /**< End key. */
        KITRA_KEY_PAGEUP = 55,   /**< Page Up key. */
        KITRA_KEY_PAGEDOWN = 56, /**< Page Down key. */
        KITRA_KEY_INSERT = 57,   /**< Insert key. */
        KITRA_KEY_DELETE = 58,   /**< Delete key. */

        /* — Control — */
        KITRA_KEY_SPACE = 59,     /**< Space bar. */
        KITRA_KEY_ENTER = 60,     /**< Enter / Return key. */
        KITRA_KEY_ESCAPE = 61,    /**< Escape key. */
        KITRA_KEY_BACKSPACE = 62, /**< Backspace key. */
        KITRA_KEY_TAB = 63,       /**< Tab key. */

        /* — Modifiers — */
        KITRA_KEY_LSHIFT = 64,   /**< Left Shift key. */
        KITRA_KEY_RSHIFT = 65,   /**< Right Shift key. */
        KITRA_KEY_LCTRL = 66,    /**< Left Control key. */
        KITRA_KEY_RCTRL = 67,    /**< Right Control key. */
        KITRA_KEY_LALT = 68,     /**< Left Alt key. */
        KITRA_KEY_RALT = 69,     /**< Right Alt key. */
        KITRA_KEY_CAPSLOCK = 70, /**< Caps Lock key. */

        /* — Punctuation & symbols — */
        KITRA_KEY_MINUS = 71,        /**< Minus / Hyphen key (@p -). */
        KITRA_KEY_EQUALS = 72,       /**< Equals key (@p =). */
        KITRA_KEY_LEFTBRACKET = 73,  /**< Left bracket key (@p [). */
        KITRA_KEY_RIGHTBRACKET = 74, /**< Right bracket key (@p ]). */
        KITRA_KEY_BACKSLASH = 75,    /**< Backslash key (@p \\). */
        KITRA_KEY_SEMICOLON = 76,    /**< Semicolon key (@p ;). */
        KITRA_KEY_APOSTROPHE = 77,   /**< Apostrophe key (@p '). */
        KITRA_KEY_GRAVE = 78,        /**< Grave accent / backtick key (@p `). */
        KITRA_KEY_COMMA = 79,        /**< Comma key (@p ,). */
        KITRA_KEY_PERIOD = 80,       /**< Period key (@p .). */
        KITRA_KEY_SLASH = 81,        /**< Forward slash key (@p /). */

        /* — Keypad — */
        KITRA_KEY_KP0 = 82,         /**< Keypad 0. */
        KITRA_KEY_KP1 = 83,         /**< Keypad 1. */
        KITRA_KEY_KP2 = 84,         /**< Keypad 2. */
        KITRA_KEY_KP3 = 85,         /**< Keypad 3. */
        KITRA_KEY_KP4 = 86,         /**< Keypad 4. */
        KITRA_KEY_KP5 = 87,         /**< Keypad 5. */
        KITRA_KEY_KP6 = 88,         /**< Keypad 6. */
        KITRA_KEY_KP7 = 89,         /**< Keypad 7. */
        KITRA_KEY_KP8 = 90,         /**< Keypad 8. */
        KITRA_KEY_KP9 = 91,         /**< Keypad 9. */
        KITRA_KEY_KP_ENTER = 92,    /**< Keypad Enter. */
        KITRA_KEY_KP_PLUS = 93,     /**< Keypad Plus (@p +). */
        KITRA_KEY_KP_MINUS = 94,    /**< Keypad Minus (@p -). */
        KITRA_KEY_KP_MULTIPLY = 95, /**< Keypad Multiply (@p *). */
        KITRA_KEY_KP_DIVIDE = 96,   /**< Keypad Divide (@p /). */

        /* — System — */
        KITRA_KEY_PRINTSCREEN = 97, /**< Print Screen key. */
        KITRA_KEY_SCROLLLOCK = 98,  /**< Scroll Lock key. */
        KITRA_KEY_PAUSE = 99,       /**< Pause / Break key. */

        KITRA_KEY_COUNT /**< Total number of tracked keys — use for sizing per-key arrays. */

    } KitraKey;

    /**
     * @brief Mouse button identifiers.
     *
     * Platform-independent button codes used throughout the input API. Values are
     * stable integers that can be used as array indices. @p KITRA_MOUSE_BUTTON_COUNT
     * gives the total number of tracked buttons and is suitable for sizing
     * per-button arrays.
     *
     * @see KitraIsMouseButtonDown, KitraIsMouseButtonPressed, KitraIsMouseButtonReleased
     */
    typedef enum KitraMouseButton
    {
        KITRA_MOUSE_LEFT = 0,   /**< Primary (left) mouse button. */
        KITRA_MOUSE_RIGHT = 1,  /**< Secondary (right) mouse button. */
        KITRA_MOUSE_MIDDLE = 2, /**< Middle mouse button / scroll wheel click. */
        KITRA_MOUSE_SIDE1 = 3,  /**< First side button (typically Back). */
        KITRA_MOUSE_SIDE2 = 4,  /**< Second side button (typically Forward). */

        KITRA_MOUSE_BUTTON_COUNT /**< Total number of tracked buttons — use for sizing per-button arrays. */

    } KitraMouseButton;

    /**
     * @brief Returns whether a key is currently held down.
     *
     * @param key  Key to query.
     * @return     @p true if @p key is held this frame, @p false otherwise or
     *             if @p key is out of range.
     *
     * @see KitraIsKeyPressed, KitraIsKeyReleased, KitraKey
     */
    bool KitraIsKeyDown(KitraKey key);

    /**
     * @brief Returns whether a key was pressed this frame.
     *
     * Only @p true on the single frame the key transitions from up to down.
     * Use @p KitraIsKeyDown for continuous held-key detection.
     *
     * @param key  Key to query.
     * @return     @p true if @p key was pressed this frame, @p false otherwise
     *             or if @p key is out of range.
     *
     * @see KitraIsKeyDown, KitraIsKeyReleased, KitraKey
     */
    bool KitraIsKeyPressed(KitraKey key);

    /**
     * @brief Returns whether a key was released this frame.
     *
     * Only @p true on the single frame the key transitions from down to up.
     *
     * @param key  Key to query.
     * @return     @p true if @p key was released this frame, @p false otherwise
     *             or if @p key is out of range.
     *
     * @see KitraIsKeyDown, KitraIsKeyPressed, KitraKey
     */
    bool KitraIsKeyReleased(KitraKey key);

    /**
     * @brief Returns the current mouse cursor position.
     *
     * Position is in screen coordinates relative to the top-left corner of
     * the window.
     *
     * @return  Current cursor position as a @p KitraPoint.
     *
     * @see KitraGetMouseDelta, KitraGetScrollDelta
     */
    KitraPoint KitraGetMousePos(void);

    /**
     * @brief Returns the mouse cursor movement since the last frame.
     *
     * Useful for camera controls or any logic that responds to relative
     * mouse motion rather than absolute position.
     *
     * @return  Per-frame cursor delta as a @p KitraVec2i.
     *
     * @see KitraGetMousePos, KitraGetScrollDelta
     */
    KitraVec2i KitraGetMouseDelta(void);

    /**
     * @brief Returns the scroll wheel delta since the last frame.
     *
     * The x component represents horizontal scroll and the y component
     * represents vertical scroll, where positive y is scroll up.
     *
     * @return  Per-frame scroll delta as a @p KitraVec2i.
     *
     * @see KitraGetMousePos, KitraGetMouseDelta
     */
    KitraVec2i KitraGetScrollDelta(void);

    /**
     * @brief Returns whether a mouse button is currently held down.
     *
     * @param button  Button to query.
     * @return        @p true if @p button is held this frame, @p false otherwise
     *                or if @p button is out of range.
     *
     * @see KitraIsMouseButtonPressed, KitraIsMouseButtonReleased, KitraMouseButton
     */
    bool KitraIsMouseButtonDown(KitraMouseButton button);

    /**
     * @brief Returns whether a mouse button was pressed this frame.
     *
     * Only @p true on the single frame the button transitions from up to down.
     * Use @p KitraIsMouseButtonDown for continuous held-button detection.
     *
     * @param button  Button to query.
     * @return        @p true if @p button was pressed this frame, @p false otherwise
     *                or if @p button is out of range.
     *
     * @see KitraIsMouseButtonDown, KitraIsMouseButtonReleased, KitraMouseButton
     */
    bool KitraIsMouseButtonPressed(KitraMouseButton button);

    /**
     * @brief Returns whether a mouse button was released this frame.
     *
     * Only @p true on the single frame the button transitions from down to up.
     *
     * @param button  Button to query.
     * @return        @p true if @p button was released this frame, @p false otherwise
     *                or if @p button is out of range.
     *
     * @see KitraIsMouseButtonDown, KitraIsMouseButtonPressed, KitraMouseButton
     */
    bool KitraIsMouseButtonReleased(KitraMouseButton button);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_INPUT_H_ */