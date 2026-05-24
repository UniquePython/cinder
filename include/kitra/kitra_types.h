#ifndef KITRA_TYPES_H_
#define KITRA_TYPES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    // ======================================= VECTORS ================================================

    /**
     * @brief A 2D integer vector.
     *
     * Can be accessed either by name (x, y) or by index (axes[0], axes[1]).
     * Commonly used for pixel positions, mouse deltas, and scroll amounts.
     *
     * @see KitraVec2f
     */
    typedef union KitraVec2i
    {
        int axes[2]; /**< Component array — axes[0] is x, axes[1] is y. */
        struct
        {
            int x; /**< Horizontal component. */
            int y; /**< Vertical component. */
        };
    } KitraVec2i;

    /**
     * @brief A 2D float vector.
     *
     * Can be accessed either by name (x, y) or by index (axes[0], axes[1]).
     * Commonly used for directions, velocities, and continuous positions.
     *
     * @see KitraVec2i
     */
    typedef union KitraVec2f
    {
        float axes[2]; /**< Component array — axes[0] is x, axes[1] is y. */
        struct
        {
            float x; /**< Horizontal component. */
            float y; /**< Vertical component. */
        };
    } KitraVec2f;

    // ======================================= SCREEN TYPES ================================================

    /**
     * @brief A 2D integer point representing a position.
     *
     * Can be accessed either by name (x, y) or by index (asArray[0], asArray[1]).
     * Commonly used for window coordinates, mouse positions, and draw targets.
     *
     * @see KitraSize, KitraRect
     */
    typedef union KitraPoint
    {
        int asArray[2]; /**< Component array — asArray[0] is x, asArray[1] is y. */
        struct
        {
            int x; /**< Horizontal position. */
            int y; /**< Vertical position. */
        };
    } KitraPoint;

    /**
     * @brief A 2D integer size representing dimensions.
     *
     * Can be accessed either by name (w, h) or by index (asArray[0], asArray[1]).
     * Commonly used for window dimensions, texture sizes, and bounding boxes.
     *
     * @see KitraPoint, KitraRect
     */
    typedef union KitraSize
    {
        int asArray[2]; /**< Component array — asArray[0] is w, asArray[1] is h. */
        struct
        {
            int w; /**< Width. */
            int h; /**< Height. */
        };
    } KitraSize;

    // ======================================= SHAPES ================================================

    /**
     * @brief A 2D integer rectangle.
     *
     * Can be accessed as individual components (x, y, w, h) or as a
     * position and size pair (pos, size).
     *
     * @see KitraPoint, KitraSize, KitraCircle
     */
    typedef union KitraRect
    {
        struct
        {
            int x; /**< Horizontal position of the top-left corner. */
            int y; /**< Vertical position of the top-left corner. */
            int w; /**< Width. */
            int h; /**< Height. */
        };
        struct
        {
            KitraPoint pos; /**< Position of the top-left corner. */
            KitraSize size; /**< Dimensions of the rectangle. */
        };
    } KitraRect;

    /**
     * @brief A 2D integer circle.
     *
     * Can be accessed as individual components (x, y, r) or as a
     * center point and radius (center, radius).
     *
     * @see KitraPoint, KitraEllipse
     */
    typedef union KitraCircle
    {
        struct
        {
            int x; /**< Horizontal position of the center. */
            int y; /**< Vertical position of the center. */
            int r; /**< Radius. */
        };
        struct
        {
            KitraPoint center; /**< Center point of the circle. */
            int radius;        /**< Radius of the circle. */
        };
    } KitraCircle;

    /**
     * @brief A 2D integer ellipse.
     *
     * Can be accessed as individual components (x, y, rx, ry) or as a
     * center point and radius pair (center, radius).
     *
     * @see KitraPoint, KitraCircle
     */
    typedef union KitraEllipse
    {
        struct
        {
            int x;  /**< Horizontal position of the center. */
            int y;  /**< Vertical position of the center. */
            int rx; /**< Horizontal radius. */
            int ry; /**< Vertical radius. */
        };
        struct
        {
            KitraPoint center; /**< Center point of the ellipse. */
            KitraPoint radius; /**< Horizontal (x) and vertical (y) radii. */
        };
    } KitraEllipse;

    // ======================================= RENDERING PRIMITIVES ================================================

    /**
     * @brief An RGBA color with 8 bits per channel.
     *
     * Each component ranges from 0 to 255. The alpha channel controls
     * transparency — 0 is fully transparent, 255 is fully opaque.
     *
     * @see KITRA_BLACK, KITRA_WHITE, KitraColorLerp(), KitraColorFromU32()
     */
    typedef struct KitraColor
    {
        uint8_t r; /**< Red channel (0–255). */
        uint8_t g; /**< Green channel (0–255). */
        uint8_t b; /**< Blue channel (0–255). */
        uint8_t a; /**< Alpha channel (0–255). 0 = fully transparent, 255 = fully opaque. */
    } KitraColor;

    /**
     * @brief Blend modes controlling how a texture is composited onto the render target.
     *
     * Passed to blending functions to control how source and destination pixel
     * colours are combined during rendering.
     *
     * @see KitraSetTextureBlendMode, KitraSetBlendMode
     */
    typedef enum KitraBlendMode
    {
        KITRA_BLEND_NONE,     /**< No blending — source pixels overwrite the destination. */
        KITRA_BLEND_ALPHA,    /**< Alpha blending — source is composited over destination using its alpha channel. */
        KITRA_BLEND_ADDITIVE, /**< Additive blending — source colour is added to the destination, brightening it. */
        KITRA_BLEND_MULTIPLY, /**< Multiply blending — source and destination colours are multiplied together, darkening the result. */
    } KitraBlendMode;

#ifdef __cplusplus
}
#endif

#endif /* KITRA_TYPES_H_ */