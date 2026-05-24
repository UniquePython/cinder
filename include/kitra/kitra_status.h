#ifndef KITRA_STATUS_H_
#define KITRA_STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Return codes used throughout the Kitra API.
     *
     * Every Kitra function that can fail and does not return a pointer returns a
     * KitraStatus value. Check against KITRA_STATUS_OK to determine success.
     *
     * @see KitraGetLastError()
     */
    typedef enum
    {
        KITRA_STATUS_OK,                     /**< Operation completed successfully. */
        KITRA_STATUS_SUBSYSTEM_DOUBLE_INIT,  /**< KitraInit() was called more than once without KitraQuit(). */
        KITRA_STATUS_SUBSYSTEM_INIT_FAILED,  /**< An SDL2 subsystem failed to initialize. */
        KITRA_STATUS_WINDOW_CREATE_FAILED,   /**< The SDL2 window could not be created. */
        KITRA_STATUS_RENDERER_CREATE_FAILED, /**< The SDL2 renderer could not be created. */
        KITRA_STATUS_RENDERER_MISSING,       /**< An operation requiring a renderer was attempted before the renderer was created. */
        KITRA_STATUS_TEXTURE_NULL,           /**< A NULL texture was passed to a function that requires a valid texture. */
        KITRA_STATUS_SCREENSHOT_FAILED,      /**< The screenshot could not be saved to disk. */
        KITRA_STATUS_MSGBOX_FAILED,          /**< SDL failed to display the message box. */
    } KitraStatus;

#ifdef __cplusplus
}
#endif

#endif /* KITRA_STATUS_H_ */