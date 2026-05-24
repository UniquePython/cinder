#ifndef KITRA_DRAW_H_
#define KITRA_DRAW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_status.h"
#include "kitra_types.h"

    /**
     * @brief Clears the entire screen with the given color.
     *
     * Typically called at the start of each frame before any drawing.
     * Logs a warning and returns early if the renderer is NULL.
     *
     * @param color Fill color.
     *
     * @see KitraBeginFrame()
     */
    void KitraClearBackground(KitraColor color);

    // --------------------------------------- POINT ---------------------------------------

    /**
     * @brief Draws a single pixel at (x, y).
     *
     * @param x     Horizontal position.
     * @param y     Vertical position.
     * @param color Pixel color.
     *
     * @see KitraDrawPointP()
     */
    void KitraDrawPoint(int x, int y, KitraColor color);

    /**
     * @brief Draws a single pixel at the given point.
     *
     * Convenience wrapper around KitraDrawPoint().
     *
     * @param pos   Position.
     * @param color Pixel color.
     *
     * @see KitraDrawPoint()
     */
    void KitraDrawPointP(KitraPoint pos, KitraColor color);

    // --------------------------------------- LINE ---------------------------------------

    /**
     * @brief Draws a line between two points.
     *
     * @param x1    X coordinate of the start point.
     * @param y1    Y coordinate of the start point.
     * @param x2    X coordinate of the end point.
     * @param y2    Y coordinate of the end point.
     * @param color Line color.
     *
     * @see KitraDrawLineP(), KitraDrawLineThick()
     */
    void KitraDrawLine(int x1, int y1, int x2, int y2, KitraColor color);

    /**
     * @brief Draws a line between two points.
     *
     * Convenience wrapper around KitraDrawLine().
     *
     * @param start Start point.
     * @param end   End point.
     * @param color Line color.
     *
     * @see KitraDrawLine()
     */
    void KitraDrawLineP(KitraPoint start, KitraPoint end, KitraColor color);

    /**
     * @brief Draws a thick line between two points.
     *
     * @param x1    X coordinate of the start point.
     * @param y1    Y coordinate of the start point.
     * @param x2    X coordinate of the end point.
     * @param y2    Y coordinate of the end point.
     * @param width Line width in pixels.
     * @param color Line color.
     *
     * @see KitraDrawLineThickP(), KitraDrawLine()
     */
    void KitraDrawLineThick(int x1, int y1, int x2, int y2, int width, KitraColor color);

    /**
     * @brief Draws a thick line between two points.
     *
     * Convenience wrapper around KitraDrawLineThick().
     *
     * @param start Start point.
     * @param end   End point.
     * @param width Line width in pixels.
     * @param color Line color.
     *
     * @see KitraDrawLineThick()
     */
    void KitraDrawLineThickP(KitraPoint start, KitraPoint end, int width, KitraColor color);

    // --------------------------------------- CIRCLE ---------------------------------------

    /**
     * @brief Draws a filled circle.
     *
     * @param x      X coordinate of the center.
     * @param y      Y coordinate of the center.
     * @param radius Radius in pixels.
     * @param color  Fill color.
     *
     * @see KitraDrawCircleC(), KitraDrawCircleOutline()
     */
    void KitraDrawCircle(int x, int y, int radius, KitraColor color);

    /**
     * @brief Draws a filled circle.
     *
     * Convenience wrapper around KitraDrawCircle().
     *
     * @param circle Circle to draw.
     * @param color  Fill color.
     *
     * @see KitraDrawCircle()
     */
    void KitraDrawCircleC(KitraCircle circle, KitraColor color);

    /**
     * @brief Draws a circle outline.
     *
     * @param x      X coordinate of the center.
     * @param y      Y coordinate of the center.
     * @param radius Radius in pixels.
     * @param color  Outline color.
     *
     * @see KitraDrawCircleOutlineC(), KitraDrawCircle()
     */
    void KitraDrawCircleOutline(int x, int y, int radius, KitraColor color);

    /**
     * @brief Draws a circle outline.
     *
     * Convenience wrapper around KitraDrawCircleOutline().
     *
     * @param circle Circle to draw.
     * @param color  Outline color.
     *
     * @see KitraDrawCircleOutline()
     */
    void KitraDrawCircleOutlineC(KitraCircle circle, KitraColor color);

    // --------------------------------------- ELLIPSE ---------------------------------------

    /**
     * @brief Draws a filled ellipse.
     *
     * @param x     X coordinate of the center.
     * @param y     Y coordinate of the center.
     * @param rx    Horizontal radius in pixels.
     * @param ry    Vertical radius in pixels.
     * @param color Fill color.
     *
     * @see KitraDrawEllipseP(), KitraDrawEllipseE(), KitraDrawEllipseOutline()
     */
    void KitraDrawEllipse(int x, int y, int rx, int ry, KitraColor color);

    /**
     * @brief Draws a filled ellipse using a center point and radius.
     *
     * Convenience wrapper around KitraDrawEllipse().
     *
     * @param pos    Center point.
     * @param radius Horizontal (x) and vertical (y) radii.
     * @param color  Fill color.
     *
     * @see KitraDrawEllipse()
     */
    void KitraDrawEllipseP(KitraPoint pos, KitraPoint radius, KitraColor color);

    /**
     * @brief Draws a filled ellipse.
     *
     * Convenience wrapper around KitraDrawEllipse().
     *
     * @param ellipse Ellipse to draw.
     * @param color   Fill color.
     *
     * @see KitraDrawEllipse()
     */
    void KitraDrawEllipseE(KitraEllipse ellipse, KitraColor color);

    /**
     * @brief Draws an ellipse outline.
     *
     * @param x     X coordinate of the center.
     * @param y     Y coordinate of the center.
     * @param rx    Horizontal radius in pixels.
     * @param ry    Vertical radius in pixels.
     * @param color Outline color.
     *
     * @see KitraDrawEllipseOutlineP(), KitraDrawEllipseOutlineE(), KitraDrawEllipse()
     */
    void KitraDrawEllipseOutline(int x, int y, int rx, int ry, KitraColor color);

    /**
     * @brief Draws an ellipse outline using a center point and radius.
     *
     * Convenience wrapper around KitraDrawEllipseOutline().
     *
     * @param pos    Center point.
     * @param radius Horizontal (x) and vertical (y) radii.
     * @param color  Outline color.
     *
     * @see KitraDrawEllipseOutline()
     */
    void KitraDrawEllipseOutlineP(KitraPoint pos, KitraPoint radius, KitraColor color);

    /**
     * @brief Draws an ellipse outline.
     *
     * Convenience wrapper around KitraDrawEllipseOutline().
     *
     * @param ellipse Ellipse to draw.
     * @param color   Outline color.
     *
     * @see KitraDrawEllipseOutline()
     */
    void KitraDrawEllipseOutlineE(KitraEllipse ellipse, KitraColor color);

    // --------------------------------------- TRIANGLE ---------------------------------------

    /**
     * @brief Draws a filled triangle.
     *
     * @param x1    X coordinate of the first vertex.
     * @param y1    Y coordinate of the first vertex.
     * @param x2    X coordinate of the second vertex.
     * @param y2    Y coordinate of the second vertex.
     * @param x3    X coordinate of the third vertex.
     * @param y3    Y coordinate of the third vertex.
     * @param color Fill color.
     *
     * @see KitraDrawTriangleP(), KitraDrawTriangleOutline()
     */
    void KitraDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, KitraColor color);

    /**
     * @brief Draws a filled triangle.
     *
     * Convenience wrapper around KitraDrawTriangle().
     *
     * @param p1    First vertex.
     * @param p2    Second vertex.
     * @param p3    Third vertex.
     * @param color Fill color.
     *
     * @see KitraDrawTriangle()
     */
    void KitraDrawTriangleP(KitraPoint p1, KitraPoint p2, KitraPoint p3, KitraColor color);

    /**
     * @brief Draws a triangle outline.
     *
     * @param x1    X coordinate of the first vertex.
     * @param y1    Y coordinate of the first vertex.
     * @param x2    X coordinate of the second vertex.
     * @param y2    Y coordinate of the second vertex.
     * @param x3    X coordinate of the third vertex.
     * @param y3    Y coordinate of the third vertex.
     * @param color Outline color.
     *
     * @see KitraDrawTriangleOutlineP(), KitraDrawTriangle()
     */
    void KitraDrawTriangleOutline(int x1, int y1, int x2, int y2, int x3, int y3, KitraColor color);

    /**
     * @brief Draws a triangle outline.
     *
     * Convenience wrapper around KitraDrawTriangleOutline().
     *
     * @param p1    First vertex.
     * @param p2    Second vertex.
     * @param p3    Third vertex.
     * @param color Outline color.
     *
     * @see KitraDrawTriangleOutline()
     */
    void KitraDrawTriangleOutlineP(KitraPoint p1, KitraPoint p2, KitraPoint p3, KitraColor color);

    // --------------------------------------- POLYGON ---------------------------------------

    /**
     * @brief Draws a filled polygon.
     *
     * @p points must contain at least 3 points. Silently returns if the
     * renderer is NULL, @p points is NULL, or @p count is less than 3.
     *
     * @param points Array of vertices defining the polygon.
     * @param count  Number of vertices. Must be at least 3.
     * @param color  Fill color.
     *
     * @see KitraDrawPolygonOutline()
     */
    void KitraDrawPolygon(const KitraPoint *points, int count, KitraColor color);

    /**
     * @brief Draws a polygon outline.
     *
     * @p points must contain at least 3 points. Silently returns if the
     * renderer is NULL, @p points is NULL, or @p count is less than 3.
     *
     * @param points Array of vertices defining the polygon.
     * @param count  Number of vertices. Must be at least 3.
     * @param color  Outline color.
     *
     * @see KitraDrawPolygon()
     */
    void KitraDrawPolygonOutline(const KitraPoint *points, int count, KitraColor color);

    // --------------------------------------- RECTANGLE ---------------------------------------

    /**
     * @brief Draws a filled rectangle.
     *
     * @param rect  Rectangle to draw.
     * @param color Fill color.
     *
     * @see KitraDrawRectOutline(), KitraDrawRoundedRect()
     */
    void KitraDrawRect(KitraRect rect, KitraColor color);

    /**
     * @brief Draws a rectangle outline.
     *
     * @param rect  Rectangle to draw.
     * @param color Outline color.
     *
     * @see KitraDrawRect(), KitraDrawRoundedRectOutline()
     */
    void KitraDrawRectOutline(KitraRect rect, KitraColor color);

    /**
     * @brief Draws a filled rectangle with rounded corners.
     *
     * @param rect   Rectangle to draw.
     * @param radius Corner radius in pixels.
     * @param color  Fill color.
     *
     * @see KitraDrawRoundedRectOutline(), KitraDrawRect()
     */
    void KitraDrawRoundedRect(KitraRect rect, int radius, KitraColor color);

    /**
     * @brief Draws a rounded rectangle outline.
     *
     * @param rect   Rectangle to draw.
     * @param radius Corner radius in pixels.
     * @param color  Outline color.
     *
     * @see KitraDrawRoundedRect(), KitraDrawRectOutline()
     */
    void KitraDrawRoundedRectOutline(KitraRect rect, int radius, KitraColor color);

    // --------------------------------------- BLEND MODE ---------------------------------------

    /**
     * @brief Sets the blend mode used for primitive drawing operations.
     *
     * Controls how shapes and lines drawn with the renderer (rather than
     * textures) are composited onto the render target.
     *
     * @param mode  Blend mode to apply to subsequent draw calls.
     * @return      @p KITRA_STATUS_OK on success, or
     *              @p KITRA_STATUS_RENDERER_MISSING if the renderer is @p NULL.
     *
     * @see KitraSetTextureBlendMode, KitraBlendMode
     */
    KitraStatus KitraSetBlendMode(KitraBlendMode mode);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_DRAW_H_ */