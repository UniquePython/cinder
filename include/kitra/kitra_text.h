#ifndef KITRA_TEXT_H_
#define KITRA_TEXT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"

    typedef struct KitraFont KitraFont;
    typedef struct KitraText KitraText;

    /**
     * @brief Loads a TrueType font from a file at the given point size.
     *
     * Initializes the TTF subsystem automatically if it has not been initialized
     * yet. Allocates and returns a new @p KitraFont ready for use in text
     * rendering calls.
     *
     * @param path  Path to the TrueType (@p .ttf) font file to load.
     * @param size  Point size to render the font at. Must be greater than zero.
     * @return      Pointer to a newly allocated @p KitraFont on success, or
     *              @p NULL if @p path is @p NULL, @p size is invalid, the TTF
     *              subsystem could not be initialized, the file could not be
     *              loaded, or memory allocation failed.
     *
     * @note The caller is responsible for freeing the returned font with
     *       @p KitraDestroyFont when it is no longer needed.
     *
     * @see KitraDestroyFont, KitraDrawText
     */
    KitraFont *KitraLoadFont(const char *path, int size);

    /**
     * @brief Destroys a font and releases all associated resources.
     *
     * Closes the underlying @p TTF_Font handle and frees the @p KitraFont
     * allocation, then sets the caller's pointer to @p NULL to prevent dangling
     * references. Safe to call with @p NULL or a pointer to @p NULL.
     *
     * @param font  Address of the @p KitraFont pointer to destroy.
     *
     * @see KitraLoadFont
     */
    void KitraDestroyFont(KitraFont **font);

    /**
     * @brief Draws a UTF-8 string to the render target at the given coordinates.
     *
     * Rasterizes @p text using @p font and blits it to the render target at
     * (@p x, @p y), measured from the top-left corner of the rendered string.
     * A temporary texture is created and destroyed internally each call; for
     * frequently drawn text consider caching the result as a @p KitraTexture.
     * Does nothing if the renderer, @p font, or @p text is @p NULL.
     *
     * @param font   Font to render with.
     * @param text   UTF-8 string to render.
     * @param x      Horizontal position of the top-left corner of the text, in pixels.
     * @param y      Vertical position of the top-left corner of the text, in pixels.
     * @param color  RGBA colour to render the text in.
     *
     * @see KitraDrawTextP, KitraLoadFont, KitraColor
     */
    void KitraDrawText(KitraFont *font, const char *text, int x, int y, KitraColor color);

    /**
     * @brief Draws a UTF-8 string to the render target at a given point.
     *
     * Convenience wrapper around @p KitraDrawText that accepts a @p KitraPoint
     * instead of separate x and y coordinates.
     *
     * @param font   Font to render with.
     * @param text   UTF-8 string to render.
     * @param pos    Position of the top-left corner of the text, in pixels.
     * @param color  RGBA colour to render the text in.
     *
     * @see KitraDrawText, KitraLoadFont, KitraColor
     */
    void KitraDrawTextP(KitraFont *font, const char *text, KitraPoint pos, KitraColor color);

    /**
     * @brief Draws a formatted UTF-8 string to the render target at the given coordinates.
     *
     * Constructs a string from @p fmt and the supplied arguments using
     * @p printf-style formatting, then renders it via @p KitraDrawText.
     * The formatted string is allocated internally and freed before returning.
     *
     * @param font   Font to render with.
     * @param x      Horizontal position of the top-left corner of the text, in pixels.
     * @param y      Vertical position of the top-left corner of the text, in pixels.
     * @param color  RGBA colour to render the text in.
     * @param fmt    @p printf-style format string.
     * @param ...    Arguments for @p fmt.
     *
     * @see KitraDrawTextFP, KitraDrawText, KitraLoadFont, KitraColor
     */
    void KitraDrawTextF(KitraFont *font, int x, int y, KitraColor color, const char *fmt, ...);

    /**
     * @brief Draws a formatted UTF-8 string to the render target at a given point.
     *
     * Convenience wrapper around @p KitraDrawTextF that accepts a @p KitraPoint
     * instead of separate x and y coordinates.
     *
     * @param font   Font to render with.
     * @param pos    Position of the top-left corner of the text, in pixels.
     * @param color  RGBA colour to render the text in.
     * @param fmt    @p printf-style format string.
     * @param ...    Arguments for @p fmt.
     *
     * @see KitraDrawTextF, KitraDrawText, KitraLoadFont, KitraColor
     */
    void KitraDrawTextFP(KitraFont *font, KitraPoint pos, KitraColor color, const char *fmt, ...);

    /**
     * @brief Creates a pre-rasterized text object from a string.
     *
     * Rasterizes @p text into a @p KitraTexture-backed @p KitraText object
     * that can be drawn repeatedly without re-rasterizing each frame. Prefer
     * this over @p KitraDrawText for strings that are drawn frequently or
     * whose content changes rarely.
     *
     * @param font   Font to rasterize with.
     * @param text   UTF-8 string to rasterize.
     * @param color  RGBA colour to rasterize the text in.
     * @return       Pointer to a newly allocated @p KitraText on success, or
     *               @p NULL if the renderer, @p font, or @p text is @p NULL,
     *               rasterization fails, texture creation fails, or memory
     *               allocation fails.
     *
     * @note The caller is responsible for freeing the returned object with
     *       @p KitraDestroyText when it is no longer needed.
     *
     * @see KitraDestroyText, KitraDrawText, KitraLoadFont
     */
    KitraText *KitraCreateText(KitraFont *font, const char *text, KitraColor color);

    /**
     * @brief Draws a pre-rasterized text object at the given coordinates.
     *
     * Blits the cached texture held by @p t to the render target at (@p x, @p y),
     * measured from the top-left corner of the text. Does nothing if the
     * renderer, @p t, or its internal handle is @p NULL.
     *
     * @param t  Pre-rasterized text object to draw.
     * @param x  Horizontal position of the top-left corner of the text, in pixels.
     * @param y  Vertical position of the top-left corner of the text, in pixels.
     *
     * @see KitraDrawCachedTextP, KitraCreateText, KitraDestroyCachedText
     */
    void KitraDrawCachedText(KitraText *t, int x, int y);

    /**
     * @brief Draws a pre-rasterized text object at a given point.
     *
     * Convenience wrapper around @p KitraDrawCachedText that accepts a
     * @p KitraPoint instead of separate x and y coordinates.
     *
     * @param t    Pre-rasterized text object to draw.
     * @param pos  Position of the top-left corner of the text, in pixels.
     *
     * @see KitraDrawCachedText, KitraCreateText, KitraDestroyCachedText
     */
    void KitraDrawCachedTextP(KitraText *t, KitraPoint pos);

    /**
     * @brief Destroys a pre-rasterized text object and releases all associated resources.
     *
     * Destroys the underlying SDL texture and frees the @p KitraText allocation,
     * then sets the caller's pointer to @p NULL to prevent dangling references.
     * Safe to call with @p NULL or a pointer to @p NULL.
     *
     * @param t  Address of the @p KitraText pointer to destroy.
     *
     * @see KitraCreateText, KitraDrawCachedText
     */
    void KitraDestroyCachedText(KitraText **t);

    /**
     * @brief Measures the pixel dimensions of a rendered UTF-8 string.
     *
     * Returns the bounding box that @p text would occupy if rendered with
     * @p font, without actually drawing anything. Useful for alignment,
     * layout, and clipping calculations.
     *
     * @param font  Font to measure with.
     * @param text  UTF-8 string to measure.
     * @return      Pixel dimensions of the rendered string as a @p KitraSize,
     *              or a zero @p KitraSize if @p font or @p text is @p NULL,
     *              or if measurement fails.
     *
     * @see KitraMeasureTextF, KitraDrawText, KitraLoadFont
     */
    KitraSize KitraMeasureText(KitraFont *font, const char *text);

    /**
     * @brief Measures the pixel dimensions of a formatted UTF-8 string.
     *
     * Constructs a string from @p fmt and the supplied arguments using
     * @p printf-style formatting, then measures it via @p KitraMeasureText.
     * The formatted string is allocated internally and freed before returning.
     *
     * @param font  Font to measure with.
     * @param fmt   @p printf-style format string.
     * @param ...   Arguments for @p fmt.
     * @return      Pixel dimensions of the rendered string as a @p KitraSize,
     *              or a zero @p KitraSize if formatting fails or memory
     *              allocation fails.
     *
     * @see KitraMeasureText, KitraDrawTextF, KitraLoadFont
     */
    KitraSize KitraMeasureTextF(KitraFont *font, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_TEXT_H_ */