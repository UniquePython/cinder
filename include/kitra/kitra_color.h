#ifndef KITRA_COLOR_H_
#define KITRA_COLOR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Creates a KitraColor with explicit red, green, blue and alpha components.
 *
 * @param r Red channel (0–255).
 * @param g Green channel (0–255).
 * @param b Blue channel (0–255).
 * @param a Alpha channel (0–255). 0 = fully transparent, 255 = fully opaque.
 * @return A KitraColor with the given components.
 *
 * @see KITRA_COLOR_RGB, KitraColor
 */
#define KITRA_COLOR_RGBA(r, g, b, a) \
    (KitraColor) { r, g, b, a }

/**
 * @brief Creates an opaque KitraColor with explicit red, green and blue components.
 *
 * Equivalent to KITRA_COLOR_RGBA(r, g, b, 255).
 *
 * @param r Red channel (0–255).
 * @param g Green channel (0–255).
 * @param b Blue channel (0–255).
 * @return A fully opaque KitraColor with the given components.
 *
 * @see KITRA_COLOR_RGBA, KitraColor
 */
#define KITRA_COLOR_RGB(r, g, b) (KitraColor){r, g, b, 255}

    /** @brief Opaque black — rgb(0, 0, 0). */
    extern const KitraColor KITRA_BLACK;

    /** @brief Opaque white — rgb(255, 255, 255). */
    extern const KitraColor KITRA_WHITE;

    /** @brief Opaque red — rgb(255, 0, 0). */
    extern const KitraColor KITRA_RED;

    /** @brief Opaque green — rgb(0, 255, 0). */
    extern const KitraColor KITRA_GREEN;

    /** @brief Opaque blue — rgb(0, 0, 255). */
    extern const KitraColor KITRA_BLUE;

    /** @brief Opaque yellow — rgb(255, 255, 0). */
    extern const KitraColor KITRA_YELLOW;

    /** @brief Opaque magenta — rgb(255, 0, 255). */
    extern const KitraColor KITRA_MAGENTA;

    /** @brief Opaque cyan — rgb(0, 255, 255). */
    extern const KitraColor KITRA_CYAN;

    /** @brief Opaque orange — rgb(255, 165, 0). */
    extern const KitraColor KITRA_ORANGE;

    /** @brief Opaque purple — rgb(128, 0, 128). */
    extern const KitraColor KITRA_PURPLE;

    /** @brief Opaque medium gray — rgb(128, 128, 128). */
    extern const KitraColor KITRA_GRAY;

    /** @brief Opaque dark gray — rgb(64, 64, 64). */
    extern const KitraColor KITRA_DARK_GRAY;

    /** @brief Opaque light gray — rgb(192, 192, 192). */
    extern const KitraColor KITRA_LIGHT_GRAY;

    /** @brief Fully transparent black — rgba(0, 0, 0, 0). */
    extern const KitraColor KITRA_TRANSPARENT;

    /**
     * @brief Packs a KitraColor into a 32-bit integer in RGBA order.
     *
     * The resulting format is 0xRRGGBBAA.
     *
     * @param color Color to pack.
     * @return 32-bit unsigned integer representing the color.
     *
     * @see KitraColorFromU32
     */
    uint32_t KitraColorToU32(KitraColor color);

    /**
     * @brief Unpacks a 32-bit integer in RGBA order into a KitraColor.
     *
     * Expects the format 0xRRGGBBAA.
     *
     * @param value 32-bit unsigned integer to unpack.
     * @return KitraColor with components extracted from @p value.
     *
     * @see KitraColorToU32
     */
    KitraColor KitraColorFromU32(uint32_t value);

    /**
     * @brief Linearly interpolates between two colors.
     *
     * Interpolates each channel independently. Clamps @p t to [0, 1].
     *
     * @param a Start color (returned when @p t = 0).
     * @param b End color (returned when @p t = 1).
     * @param t Interpolation factor in [0, 1].
     * @return Interpolated color between @p a and @p b.
     *
     * @see KitraColorFade
     */
    KitraColor KitraColorLerp(KitraColor a, KitraColor b, float t);

    /**
     * @brief Returns a copy of a color with a new alpha value.
     *
     * @p alpha is a normalized float in [0, 1] — 0 is fully transparent,
     * 1 is fully opaque. Values outside this range are clamped.
     *
     * @param color Base color.
     * @param alpha Normalized alpha value in [0, 1].
     * @return Copy of @p color with the alpha channel set accordingly.
     *
     * @see KitraColorLerp
     */
    KitraColor KitraColorFade(KitraColor color, float alpha);

    /**
     * @brief Creates a KitraColor from hue, saturation and value (HSV).
     *
     * @param h Hue in degrees [0, 360). Values outside this range are wrapped.
     * @param s Saturation in [0, 1]. 0 produces a shade of gray.
     * @param v Value (brightness) in [0, 1]. 0 produces black.
     * @return Fully opaque KitraColor corresponding to the given HSV values.
     *
     * @see KitraColorToHSV
     */
    KitraColor KitraColorFromHSV(float h, float s, float v);

    /**
     * @brief Converts a KitraColor to hue, saturation and value (HSV).
     *
     * The alpha channel is ignored. Output pointers must not be NULL.
     *
     * @param color Input color.
     * @param h     Output hue in degrees [0, 360).
     * @param s     Output saturation in [0, 1].
     * @param v     Output value (brightness) in [0, 1].
     *
     * @see KitraColorFromHSV
     */
    void KitraColorToHSV(KitraColor color, float *h, float *s, float *v);

    /**
     * @brief Brightens a color by a normalized amount.
     *
     * Adds @p amount × 255 to each RGB channel, clamping at 255.
     * The alpha channel is unchanged.
     *
     * @param color  Base color.
     * @param amount Brightness increase in [0, 1].
     * @return Brightened copy of @p color.
     *
     * @see KitraColorDarken
     */
    KitraColor KitraColorBrighten(KitraColor color, float amount);

    /**
     * @brief Darkens a color by a normalized amount.
     *
     * Subtracts @p amount × 255 from each RGB channel, clamping at 0.
     * The alpha channel is unchanged.
     *
     * @param color  Base color.
     * @param amount Darkness increase in [0, 1].
     * @return Darkened copy of @p color.
     *
     * @see KitraColorBrighten
     */
    KitraColor KitraColorDarken(KitraColor color, float amount);

    /**
     * @brief Inverts the RGB channels of a color.
     *
     * Each channel is replaced with 255 minus its current value.
     * The alpha channel is unchanged.
     *
     * @param color Color to invert.
     * @return Color with inverted RGB channels.
     */
    KitraColor KitraColorInvert(KitraColor color);

    /**
     * @brief Tests whether two colors are equal.
     *
     * Compares all four channels — r, g, b, and a.
     *
     * @param a First color.
     * @param b Second color.
     * @return True if all channels are equal, false otherwise.
     */
    bool KitraColorIsEqual(KitraColor a, KitraColor b);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_COLOR_H_ */