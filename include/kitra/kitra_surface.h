#ifndef KITRA_SURFACE_H_
#define KITRA_SURFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "kitra_types.h"
#include "kitra_status.h"

    typedef struct KitraTexture KitraTexture;

    typedef struct KitraSurface KitraSurface;

    /**
     * @brief Creates a blank RGBA surface of the given dimensions.
     *
     * Allocates a new CPU-side pixel buffer with all pixels initialized
     * to transparent black (0, 0, 0, 0).
     *
     * @param w  Width in pixels.
     * @param h  Height in pixels.
     * @return   Pointer to a newly allocated @p KitraSurface on success, or
     *           @p NULL if allocation or surface creation fails.
     *
     * @see KitraLoadSurface, KitraDestroySurface
     */
    KitraSurface *KitraCreateSurface(int w, int h);

    /**
     * @brief Loads an image file as a surface.
     *
     * Allocates and returns a new @p KitraSurface backed by the decoded
     * pixel data of the image at @p path. The surface lives on the CPU
     * and is not uploaded to the GPU.
     *
     * @param path  Path to the image file to load.
     * @return      Pointer to a newly allocated @p KitraSurface on success, or
     *              @p NULL if the image subsystem could not be initialized,
     *              the file could not be loaded, or memory allocation fails.
     *
     * @see KitraCreateSurface, KitraDestroySurface, KitraSurfaceToTexture
     */
    KitraSurface *KitraLoadSurface(const char *path);

    /**
     * @brief Destroys a surface and releases all associated resources.
     *
     * Frees the underlying SDL surface and the @p KitraSurface allocation,
     * then sets the caller's pointer to @p NULL to prevent dangling references.
     * Safe to call with @p NULL or a pointer to @p NULL.
     *
     * @param surface  Address of the @p KitraSurface pointer to destroy.
     *
     * @see KitraCreateSurface, KitraLoadSurface
     */
    void KitraDestroySurface(KitraSurface **surface);

    /**
     * @brief Converts a surface to a texture, uploading it to the GPU.
     *
     * Creates a new @p KitraTexture from the pixel data of @p surface.
     * The surface is not destroyed — the caller remains responsible for
     * freeing it with @p KitraDestroySurface when it is no longer needed.
     *
     * @param surface  Surface to convert.
     * @return         Pointer to a newly allocated @p KitraTexture on success, or
     *                 @p NULL if @p surface is @p NULL, the renderer is not
     *                 initialized, or texture creation fails.
     *
     * @see KitraDestroySurface, KitraDestroyTexture
     */
    KitraTexture *KitraSurfaceToTexture(KitraSurface *surface);

    /**
     * @brief Reads the color of a pixel at the given coordinates.
     *
     * @param surface  Surface to read from.
     * @param x        Horizontal coordinate.
     * @param y        Vertical coordinate.
     * @return         Color of the pixel at (@p x, @p y), or transparent black
     *                 if @p surface is @p NULL or the coordinates are out of bounds.
     *
     * @see KitraReadPixelP, KitraWritePixel
     */
    KitraColor KitraReadPixel(KitraSurface *surface, int x, int y);

    /**
     * @brief Reads the color of a pixel at the given point.
     *
     * Convenience wrapper around @p KitraReadPixel that accepts a
     * @p KitraPoint instead of separate x and y coordinates.
     *
     * @param surface  Surface to read from.
     * @param p        Coordinates of the pixel to read.
     * @return         Color of the pixel at @p p, or transparent black
     *                 if @p surface is @p NULL or @p p is out of bounds.
     *
     * @see KitraReadPixel, KitraWritePixelP
     */
    KitraColor KitraReadPixelP(KitraSurface *surface, KitraPoint p);

    /**
     * @brief Writes a color to a pixel at the given coordinates.
     *
     * @param surface  Surface to write to.
     * @param x        Horizontal coordinate.
     * @param y        Vertical coordinate.
     * @param color    Color to write.
     *
     * @see KitraWritePixelP, KitraReadPixel
     */
    void KitraWritePixel(KitraSurface *surface, int x, int y, KitraColor color);

    /**
     * @brief Writes a color to a pixel at the given point.
     *
     * Convenience wrapper around @p KitraWritePixel that accepts a
     * @p KitraPoint instead of separate x and y coordinates.
     *
     * @param surface  Surface to write to.
     * @param p        Coordinates of the pixel to write.
     * @param color    Color to write.
     *
     * @see KitraWritePixel, KitraReadPixelP
     */
    void KitraWritePixelP(KitraSurface *surface, KitraPoint p, KitraColor color);

    /**
     * @brief Returns the pixel dimensions of a surface.
     *
     * @param surface  Surface to query.
     * @return         Dimensions of @p surface as a @p KitraSize, or a zero
     *                 @p KitraSize if @p surface is @p NULL.
     *
     * @see KitraGetTextureSize, KitraSize
     */
    KitraSize KitraGetSurfaceSize(KitraSurface *surface);

    struct SDL_Surface;

    /**
     * @brief Returns the underlying SDL surface handle.
     *
     * Provides access to the raw @p SDL_Surface pointer for interoperability
     * with SDL APIs not wrapped by Kitra. Ownership remains with @p surface —
     * do not free the returned pointer directly.
     *
     * @param surface  Surface to retrieve the handle from.
     * @return         The underlying @p SDL_Surface pointer.
     */
    struct SDL_Surface *KitraSurfaceGetSDL(KitraSurface *surface);

#ifdef __cplusplus
}
#endif

#endif /* KITRA_SURFACE_H_ */