#ifndef KITRA_MATH_H_
#define KITRA_MATH_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"

#include <math.h>
#include <stdbool.h>

/** @brief The mathematical constant π, accurate to 15 decimal places. */
#define KITRA_PI 3.141592653589793

/**
 * @brief Converts degrees to radians.
 * @param deg Angle in degrees.
 * @return Equivalent angle in radians.
 */
#define KITRA_DEG2RAD(deg) ((deg) * ((float)KITRA_PI / 180.0f))

/**
 * @brief Converts radians to degrees.
 * @param rad Angle in radians.
 * @return Equivalent angle in degrees.
 */
#define KITRA_RAD2DEG(rad) ((rad) * (180.0f / (float)KITRA_PI))

    // ======================================= VECTORS ================================================

    // --------------------------------------- 2D ---------------------------------------

    /**
     * @brief Adds two integer vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Component-wise sum of @p a and @p b.
     */
    static inline KitraVec2i KitraVec2iAdd(KitraVec2i a, KitraVec2i b)
    {
        return (KitraVec2i){{a.x + b.x, a.y + b.y}};
    }

    /**
     * @brief Adds two float vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Component-wise sum of @p a and @p b.
     */
    static inline KitraVec2f KitraVec2fAdd(KitraVec2f a, KitraVec2f b)
    {
        return (KitraVec2f){{a.x + b.x, a.y + b.y}};
    }

    /**
     * @brief Subtracts one integer vector from another.
     * @param a First vector.
     * @param b Vector to subtract from @p a.
     * @return Component-wise difference of @p a and @p b.
     */
    static inline KitraVec2i KitraVec2iSub(KitraVec2i a, KitraVec2i b)
    {
        return (KitraVec2i){{a.x - b.x, a.y - b.y}};
    }

    /**
     * @brief Subtracts one float vector from another.
     * @param a First vector.
     * @param b Vector to subtract from @p a.
     * @return Component-wise difference of @p a and @p b.
     */
    static inline KitraVec2f KitraVec2fSub(KitraVec2f a, KitraVec2f b)
    {
        return (KitraVec2f){{a.x - b.x, a.y - b.y}};
    }

    /**
     * @brief Negates an integer vector.
     * @param v Vector to negate.
     * @return Vector with both components negated.
     */
    static inline KitraVec2i KitraVec2iNegate(KitraVec2i v)
    {
        return (KitraVec2i){{-v.x, -v.y}};
    }

    /**
     * @brief Negates a float vector.
     * @param v Vector to negate.
     * @return Vector with both components negated.
     */
    static inline KitraVec2f KitraVec2fNegate(KitraVec2f v)
    {
        return (KitraVec2f){{-v.x, -v.y}};
    }

    /**
     * @brief Scales an integer vector by a scalar.
     * @param v      Vector to scale.
     * @param factor Scalar multiplier.
     * @return Vector with both components multiplied by @p factor.
     */
    static inline KitraVec2i KitraVec2iScale(KitraVec2i v, int factor)
    {
        return (KitraVec2i){{v.x * factor, v.y * factor}};
    }

    /**
     * @brief Scales a float vector by a scalar.
     * @param v      Vector to scale.
     * @param factor Scalar multiplier.
     * @return Vector with both components multiplied by @p factor.
     */
    static inline KitraVec2f KitraVec2fScale(KitraVec2f v, float factor)
    {
        return (KitraVec2f){{v.x * factor, v.y * factor}};
    }

    /**
     * @brief Returns the squared length of an integer vector.
     *
     * Cheaper than KitraVec2iLength() as it avoids a square root.
     * Useful for distance comparisons where the exact length isn't needed.
     *
     * @param v Input vector.
     * @return x² + y².
     */
    static inline int KitraVec2iLengthSquared(KitraVec2i v)
    {
        return v.x * v.x + v.y * v.y;
    }

    /**
     * @brief Returns the squared length of a float vector.
     *
     * Cheaper than KitraVec2fLength() as it avoids a square root.
     * Useful for distance comparisons where the exact length isn't needed.
     *
     * @param v Input vector.
     * @return x² + y².
     */
    static inline float KitraVec2fLengthSquared(KitraVec2f v)
    {
        return v.x * v.x + v.y * v.y;
    }

    /**
     * @brief Returns the length of an integer vector.
     * @param v Input vector.
     * @return Euclidean length — √(x² + y²).
     */
    static inline float KitraVec2iLength(KitraVec2i v)
    {
        return sqrtf(KitraVec2iLengthSquared(v));
    }

    /**
     * @brief Returns the length of a float vector.
     * @param v Input vector.
     * @return Euclidean length — √(x² + y²).
     */
    static inline float KitraVec2fLength(KitraVec2f v)
    {
        return sqrtf(KitraVec2fLengthSquared(v));
    }

    /**
     * @brief Computes the dot product of two integer vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Scalar dot product — a.x*b.x + a.y*b.y.
     */
    static inline int KitraVec2iDot(KitraVec2i a, KitraVec2i b)
    {
        return a.x * b.x + a.y * b.y;
    }

    /**
     * @brief Computes the dot product of two float vectors.
     * @param a First vector.
     * @param b Second vector.
     * @return Scalar dot product — a.x*b.x + a.y*b.y.
     */
    static inline float KitraVec2fDot(KitraVec2f a, KitraVec2f b)
    {
        return a.x * b.x + a.y * b.y;
    }

    /**
     * @brief Normalizes a float vector to unit length.
     *
     * Returns a zero vector if the input length is zero, to avoid
     * division by zero.
     *
     * @param v Vector to normalize.
     * @return Unit vector in the same direction as @p v, or (0, 0) if @p v is zero.
     */
    static inline KitraVec2f KitraVec2fNormalize(KitraVec2f v)
    {
        float len = KitraVec2fLength(v);
        if (len == 0.0f)
            return (KitraVec2f){{0.0f, 0.0f}};
        return (KitraVec2f){{v.x / len, v.y / len}};
    }

    /**
     * @brief Linearly interpolates between two float vectors.
     * @param a Start vector (returned when @p t = 0).
     * @param b End vector (returned when @p t = 1).
     * @param t Interpolation factor, typically in [0, 1].
     * @return Interpolated vector between @p a and @p b.
     */
    static inline KitraVec2f KitraVec2fLerp(KitraVec2f a, KitraVec2f b, float t)
    {
        return (KitraVec2f){{a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t}};
    }

    /**
     * @brief Rotates a float vector by an angle.
     * @param v     Vector to rotate.
     * @param angle Rotation angle in radians, measured counter-clockwise.
     * @return Rotated vector.
     */
    static inline KitraVec2f KitraVec2fRotate(KitraVec2f v, float angle)
    {
        float c = cosf(angle);
        float s = sinf(angle);
        return (KitraVec2f){{v.x * c - v.y * s, v.x * s + v.y * c}};
    }

    /**
     * @brief Computes the 2D cross product of two integer vectors.
     *
     * Returns the Z component of the 3D cross product, which indicates
     * the signed area of the parallelogram formed by @p a and @p b.
     * Positive means @p b is counter-clockwise from @p a.
     *
     * @param a First vector.
     * @param b Second vector.
     * @return a.x*b.y - a.y*b.x.
     */
    static inline int KitraVec2iCross(KitraVec2i a, KitraVec2i b)
    {
        return a.x * b.y - a.y * b.x;
    }

    /**
     * @brief Computes the 2D cross product of two float vectors.
     *
     * Returns the Z component of the 3D cross product, which indicates
     * the signed area of the parallelogram formed by @p a and @p b.
     * Positive means @p b is counter-clockwise from @p a.
     *
     * @param a First vector.
     * @param b Second vector.
     * @return a.x*b.y - a.y*b.x.
     */
    static inline float KitraVec2fCross(KitraVec2f a, KitraVec2f b)
    {
        return a.x * b.y - a.y * b.x;
    }

    /**
     * @brief Returns the angle of a float vector in radians.
     * @param v Input vector.
     * @return Angle from the positive X axis in radians, in the range [-π, π].
     */
    static inline float KitraVec2fAngle(KitraVec2f v)
    {
        return atan2f(v.y, v.x);
    }

    // ======================================= COLLISION ================================================

    /**
     * @brief Returns the distance between two points.
     *
     * @param a  First point.
     * @param b  Second point.
     * @return   Euclidean distance between @p a and @p b in pixels.
     *
     * @see KitraPointRectDistance, KitraPointCircleDistance
     */
    static inline float KitraPointPointDistance(KitraPoint a, KitraPoint b)
    {
        float dx = (float)(a.x - b.x);
        float dy = (float)(a.y - b.y);
        return sqrtf(dx * dx + dy * dy);
    }

    /**
     * @brief Returns the signed distance between a point and a rectangle.
     *
     * Positive values indicate the point lies outside @p rect; negative values
     * indicate it lies inside, with the magnitude representing the depth of
     * penetration to the nearest edge.
     *
     * @param p     Point to test.
     * @param rect  Rectangle to test against.
     * @return      Signed distance from @p p to the nearest edge of @p rect,
     *              in pixels.
     *
     * @see KitraPointPointDistance, KitraRectRectDistance
     */
    static inline float KitraPointRectDistance(KitraPoint p, KitraRect rect)
    {
        int cx = p.x < rect.x ? rect.x : p.x > rect.x + rect.w ? rect.x + rect.w
                                                               : p.x;
        int cy = p.y < rect.y ? rect.y : p.y > rect.y + rect.h ? rect.y + rect.h
                                                               : p.y;
        float dx = (float)(p.x - cx);
        float dy = (float)(p.y - cy);
        float outside = sqrtf(dx * dx + dy * dy);
        if (outside > 0.0f)
            return outside;
        float dLeft = (float)(p.x - rect.x);
        float dRight = (float)(rect.x + rect.w - p.x);
        float dTop = (float)(p.y - rect.y);
        float dBottom = (float)(rect.y + rect.h - p.y);
        float minDist = dLeft < dRight ? dLeft : dRight;
        if (dTop < minDist)
            minDist = dTop;
        if (dBottom < minDist)
            minDist = dBottom;
        return -minDist;
    }

    /**
     * @brief Returns the signed distance between a point and a circle.
     *
     * Positive values indicate the point lies outside @p circle; negative values
     * indicate it lies inside.
     *
     * @param p       Point to test.
     * @param circle  Circle to test against.
     * @return        Signed distance from @p p to the circumference of @p circle,
     *                in pixels.
     *
     * @see KitraPointPointDistance, KitraCircleCircleDistance
     */
    static inline float KitraPointCircleDistance(KitraPoint p, KitraCircle circle)
    {
        float dx = (float)(p.x - circle.x);
        float dy = (float)(p.y - circle.y);
        return sqrtf(dx * dx + dy * dy) - (float)circle.radius;
    }

    /**
     * @brief Returns the approximate signed distance between a point and an ellipse.
     *
     * Uses a Euler approximation of the ellipse radius in the direction of @p p
     * to estimate the signed distance. Positive values indicate the point lies
     * outside @p ellipse; negative values indicate it lies inside.
     *
     * @param p        Point to test.
     * @param ellipse  Ellipse to test against.
     * @return         Approximate signed distance from @p p to the boundary of
     *                 @p ellipse, in pixels.
     *
     * @see KitraPointCircleDistance, KitraEllipseEllipseDistance
     */
    static inline float KitraPointEllipseDistance(KitraPoint p, KitraEllipse ellipse)
    {
        float dx = (float)(p.x - ellipse.x) / (float)ellipse.rx;
        float dy = (float)(p.y - ellipse.y) / (float)ellipse.ry;
        float normalized = sqrtf(dx * dx + dy * dy);
        float rx = (float)ellipse.rx;
        float ry = (float)ellipse.ry;
        float avgRadius = (2.0f * rx * ry) / (rx + ry);
        return (normalized - 1.0f) * avgRadius;
    }

    /**
     * @brief Returns the signed distance between two rectangles.
     *
     * Positive values indicate the rectangles are separated, with the magnitude
     * equal to the gap between their nearest edges. Negative values indicate
     * overlap, with the magnitude representing the minimum penetration depth
     * along either axis.
     *
     * @param a  First rectangle.
     * @param b  Second rectangle.
     * @return   Signed distance between @p a and @p b, in pixels.
     *
     * @see KitraPointRectDistance, KitraRectCircleDistance
     */
    static inline float KitraRectRectDistance(KitraRect a, KitraRect b)
    {
        float dx = 0.0f, dy = 0.0f;
        if (b.x + b.w <= a.x)
            dx = (float)(a.x - (b.x + b.w));
        else if (a.x + a.w <= b.x)
            dx = (float)(b.x - (a.x + a.w));
        if (b.y + b.h <= a.y)
            dy = (float)(a.y - (b.y + b.h));
        else if (a.y + a.h <= b.y)
            dy = (float)(b.y - (a.y + a.h));
        if (dx > 0.0f || dy > 0.0f)
            return sqrtf(dx * dx + dy * dy);
        float dLeft = (float)(a.x - b.x);
        float dRight = (float)((b.x + b.w) - (a.x + a.w));
        float dTop = (float)(a.y - b.y);
        float dBottom = (float)((b.y + b.h) - (a.y + a.h));
        float minPen = dLeft < dRight ? dLeft : dRight;
        if (dTop < minPen)
            minPen = dTop;
        if (dBottom < minPen)
            minPen = dBottom;
        return -minPen;
    }

    /**
     * @brief Returns the signed distance between a rectangle and a circle.
     *
     * Positive values indicate the shapes are separated; negative values indicate
     * overlap, with the magnitude equal to the penetration depth.
     *
     * @param rect    Rectangle to test.
     * @param circle  Circle to test against.
     * @return        Signed distance between @p rect and @p circle, in pixels.
     *
     * @see KitraRectRectDistance, KitraCircleCircleDistance
     */
    static inline float KitraRectCircleDistance(KitraRect rect, KitraCircle circle)
    {
        int cx = circle.x < rect.x ? rect.x : circle.x > rect.x + rect.w ? rect.x + rect.w
                                                                         : circle.x;
        int cy = circle.y < rect.y ? rect.y : circle.y > rect.y + rect.h ? rect.y + rect.h
                                                                         : circle.y;
        float dx = (float)(circle.x - cx);
        float dy = (float)(circle.y - cy);
        float dist = sqrtf(dx * dx + dy * dy);
        return dist - (float)circle.radius;
    }

    /**
     * @brief Returns the approximate signed distance between a rectangle and an ellipse.
     *
     * Clamps the ellipse centre to the nearest point on @p rect, then estimates
     * the signed distance using a Euler radius approximation. Positive values
     * indicate separation; negative values indicate overlap.
     *
     * @param rect     Rectangle to test.
     * @param ellipse  Ellipse to test against.
     * @return         Approximate signed distance between @p rect and @p ellipse,
     *                 in pixels.
     *
     * @see KitraRectCircleDistance, KitraEllipseEllipseDistance
     */
    static inline float KitraRectEllipseDistance(KitraRect rect, KitraEllipse ellipse)
    {
        int cx = ellipse.x < rect.x ? rect.x : ellipse.x > rect.x + rect.w ? rect.x + rect.w
                                                                           : ellipse.x;
        int cy = ellipse.y < rect.y ? rect.y : ellipse.y > rect.y + rect.h ? rect.y + rect.h
                                                                           : ellipse.y;
        float dx = (float)(ellipse.x - cx) / (float)ellipse.rx;
        float dy = (float)(ellipse.y - cy) / (float)ellipse.ry;
        float normalized = sqrtf(dx * dx + dy * dy);
        float rx = (float)ellipse.rx;
        float ry = (float)ellipse.ry;
        float avgRadius = (2.0f * rx * ry) / (rx + ry);
        return (normalized - 1.0f) * avgRadius;
    }

    /**
     * @brief Returns the signed distance between two circles.
     *
     * Positive values indicate the circles are separated; negative values indicate
     * overlap, with the magnitude equal to the penetration depth.
     *
     * @param a  First circle.
     * @param b  Second circle.
     * @return   Signed distance between @p a and @p b, in pixels.
     *
     * @see KitraCircleEllipseDistance, KitraRectCircleDistance
     */
    static inline float KitraCircleCircleDistance(KitraCircle a, KitraCircle b)
    {
        float dx = (float)(a.x - b.x);
        float dy = (float)(a.y - b.y);
        return sqrtf(dx * dx + dy * dy) - (float)(a.radius + b.radius);
    }

    /**
     * @brief Returns the approximate signed distance between a circle and an ellipse.
     *
     * Estimates the signed distance by normalizing into ellipse space and applying
     * a Euler radius approximation, then subtracting the circle radius. Positive
     * values indicate separation; negative values indicate overlap.
     *
     * @param circle   Circle to test.
     * @param ellipse  Ellipse to test against.
     * @return         Approximate signed distance between @p circle and @p ellipse,
     *                 in pixels.
     *
     * @see KitraCircleCircleDistance, KitraEllipseEllipseDistance
     */
    static inline float KitraCircleEllipseDistance(KitraCircle circle, KitraEllipse ellipse)
    {
        float dx = (float)(circle.x - ellipse.x) / (float)ellipse.rx;
        float dy = (float)(circle.y - ellipse.y) / (float)ellipse.ry;
        float normalized = sqrtf(dx * dx + dy * dy);
        float rx = (float)ellipse.rx;
        float ry = (float)ellipse.ry;
        float avgRadius = (2.0f * rx * ry) / (rx + ry);
        return (normalized - 1.0f) * avgRadius - (float)circle.radius;
    }

    /**
     * @brief Returns the approximate signed distance between two ellipses.
     *
     * Normalizes the centre separation by the mean radii of the two ellipses and
     * applies a Euler radius approximation to estimate the signed distance.
     * Positive values indicate separation; negative values indicate overlap.
     *
     * @param a  First ellipse.
     * @param b  Second ellipse.
     * @return   Approximate signed distance between @p a and @p b, in pixels.
     *
     * @see KitraCircleEllipseDistance, KitraRectEllipseDistance
     */
    static inline float KitraEllipseEllipseDistance(KitraEllipse a, KitraEllipse b)
    {
        float dx = (float)(a.x - b.x) / ((float)(a.rx + b.rx) * 0.5f);
        float dy = (float)(a.y - b.y) / ((float)(a.ry + b.ry) * 0.5f);
        float normalized = sqrtf(dx * dx + dy * dy);
        float avgRx = (float)(a.rx + b.rx) * 0.5f;
        float avgRy = (float)(a.ry + b.ry) * 0.5f;
        float avgRadius = (2.0f * avgRx * avgRy) / (avgRx + avgRy);
        return (normalized - 1.0f) * avgRadius;
    }

    // ======================================= EASING ================================================

    /**
     * @brief Linear easing — no acceleration or deceleration.
     * @param t Interpolation factor in [0, 1].
     * @return @p t unchanged.
     */
    static inline float KitraEaseLinear(float t)
    {
        return t;
    }

    /**
     * @brief Quadratic ease-in — accelerates from zero.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseInQuad(float t)
    {
        return t * t;
    }

    /**
     * @brief Quadratic ease-out — decelerates to zero.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseOutQuad(float t)
    {
        return t * (2.0f - t);
    }

    /**
     * @brief Quadratic ease-in-out — accelerates then decelerates.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseInOutQuad(float t)
    {
        return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
    }

    /**
     * @brief Sine ease-in — accelerates from zero using a sine curve.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseInSine(float t)
    {
        return 1.0f - cosf(t * (float)KITRA_PI * 0.5f);
    }

    /**
     * @brief Sine ease-out — decelerates to zero using a sine curve.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseOutSine(float t)
    {
        return sinf(t * (float)KITRA_PI * 0.5f);
    }

    /**
     * @brief Sine ease-in-out — accelerates then decelerates using a sine curve.
     * @param t Interpolation factor in [0, 1].
     * @return Eased value in [0, 1].
     */
    static inline float KitraEaseInOutSine(float t)
    {
        return 0.5f * (1.0f - cosf(t * (float)KITRA_PI));
    }

    /**
     * @brief Back ease-in — overshoots slightly before moving forward.
     *
     * Uses a back constant of 1.70158, producing a small negative dip
     * at the start before accelerating forward.
     *
     * @param t Interpolation factor in [0, 1].
     * @return Eased value, may dip slightly below 0 at the start.
     */
    static inline float KitraEaseInBack(float t)
    {
        const float c = 1.70158f;
        return t * t * ((c + 1.0f) * t - c);
    }

    /**
     * @brief Back ease-out — overshoots the target then settles back.
     *
     * Uses a back constant of 1.70158, producing a small overshoot
     * past 1 before settling at the final value.
     *
     * @param t Interpolation factor in [0, 1].
     * @return Eased value, may briefly exceed 1 near the end.
     */
    static inline float KitraEaseOutBack(float t)
    {
        const float c = 1.70158f;
        float u = t - 1.0f;
        return u * u * ((c + 1.0f) * u + c) + 1.0f;
    }

#ifdef __cplusplus
}
#endif

#endif /* KITRA_MATH_H_ */