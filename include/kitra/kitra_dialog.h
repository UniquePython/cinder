#ifndef KITRA_DIALOG_H_
#define KITRA_DIALOG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_status.h"
#include <stdbool.h>

    /**
     * @brief Severity/icon type for message boxes and dialogs.
     *
     * Controls the icon displayed in the message box and maps to the
     * equivalent SDL_MessageBoxFlags value internally.
     *
     * @see KitraShowMessageBox, KitraShowDialog
     */
    typedef enum KitraMessageBoxType
    {
        KITRA_MSGBOX_INFO,    /**< Informational message — neutral icon. */
        KITRA_MSGBOX_WARNING, /**< Warning — caution icon. */
        KITRA_MSGBOX_ERROR,   /**< Error — stop icon. */
    } KitraMessageBoxType;

    /**
     * @brief A labeled button in a custom dialog.
     *
     * @p id is returned by KitraShowDialog when the button is clicked.
     * Use distinct non-negative values; -1 is reserved for errors.
     *
     * @see KitraShowDialog
     */
    typedef struct KitraMessageBoxButton
    {
        int id;           /**< Value returned when this button is clicked. */
        const char *text; /**< Button label. */
    } KitraMessageBoxButton;

    /**
     * @brief Displays a simple message box with a single dismiss button.
     *
     * Blocks until the user closes the box. Uses the active window as the
     * parent if one exists. Does nothing and returns early if @p title or
     * @p message is NULL.
     *
     * @param type     Icon/severity to display.
     * @param title    Title bar text.
     * @param message  Body text.
     * @return         @p KITRA_STATUS_OK on success, or
     *                 @p KITRA_STATUS_MSGBOX_FAILED if SDL could not
     *                 display the box.
     *
     * @see KitraShowDialog, KitraMessageBoxType
     */
    KitraStatus KitraShowMessageBox(KitraMessageBoxType type, const char *title, const char *message);

    /**
     * @brief Displays a message box with custom buttons and returns which was clicked.
     *
     * Blocks until the user clicks a button. Uses the active window as the
     * parent if one exists. Returns -1 on error or if the box is dismissed
     * without a button click.
     *
     * @param type     Icon/severity to display.
     * @param title    Title bar text.
     * @param message  Body text.
     * @param buttons  Array of buttons to display.
     * @param count    Number of buttons. Must be at least 1.
     * @return         The @p id of the clicked button, or -1 on failure.
     *
     * @see KitraShowMessageBox, KitraMessageBoxButton
     */
    int KitraShowDialog(KitraMessageBoxType type, const char *title, const char *message, const KitraMessageBoxButton *buttons, int count);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_DIALOG_H_ */