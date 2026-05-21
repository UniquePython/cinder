#include "kitra_internal.h"

struct KitraTexture
{
    SDL_Texture *handle;
    int width, height;
};

KitraTexture *KitraLoadTexture(const char *path)
{
    if (!gKitraCtx.core.imgInitialized)
    {
        int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF;
        int impFormats = IMG_INIT_PNG | IMG_INIT_JPG;

        if ((IMG_Init(flags) & impFormats) != impFormats)
        {
            KITRA_LOG(KITRA_LOG_ERROR, IMG_GetError());
            return NULL;
        }
        gKitraCtx.core.imgInitialized = true;
    }

    if (!gKitraCtx.core.renderer)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Renderer not initialized");
        return NULL;
    }

    SDL_Surface *surface = IMG_Load(path);
    if (!surface)
    {
        KITRA_LOG(KITRA_LOG_ERROR, IMG_GetError());
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(gKitraCtx.core.renderer, surface);
    SDL_FreeSurface(surface);

    if (!tex)
    {
        KITRA_LOG(KITRA_LOG_ERROR, SDL_GetError());
        return NULL;
    }

    KitraTexture *cTex = malloc(sizeof(KitraTexture));
    if (!cTex)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Failed to allocate KitraTexture");
        SDL_DestroyTexture(tex);
        return NULL;
    }

    cTex->handle = tex;
    SDL_QueryTexture(tex, NULL, NULL, &cTex->width, &cTex->height);

    return cTex;
}

void KitraDestroyTexture(KitraTexture **tex)
{
    if (!tex || !*tex)
        return;

    SDL_DestroyTexture((*tex)->handle);
    free(*tex);
    *tex = NULL;
}

KitraSize KitraGetTextureSize(const KitraTexture *tex)
{
    if (!tex)
    {
        KITRA_LOG(KITRA_LOG_WARNING, "Texture is NULL in KitraGetTextureSize");
        return (KitraSize){{0, 0}};
    }

    return (KitraSize){{tex->width, tex->height}};
}

KitraStatus KitraScreenshot(const char *path)
{
    if (!path)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Path is NULL in KitraScreenshot");
        return KITRA_STATUS_SCREENSHOT_FAILED;
    }

    if (!gKitraCtx.core.renderer)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Renderer is NULL in KitraScreenshot");
        return KITRA_STATUS_SCREENSHOT_FAILED;
    }

    KitraSize size = KitraGetWindowSize();

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(
        0, size.w, size.h, 32, SDL_PIXELFORMAT_RGBA32);

    if (!surface)
    {
        KITRA_LOG(KITRA_LOG_ERROR, SDL_GetError());
        return KITRA_STATUS_SCREENSHOT_FAILED;
    }

    if (SDL_RenderReadPixels(gKitraCtx.core.renderer, NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0)
    {
        KITRA_LOG(KITRA_LOG_ERROR, SDL_GetError());
        SDL_FreeSurface(surface);
        return KITRA_STATUS_SCREENSHOT_FAILED;
    }

    if (IMG_SavePNG(surface, path) != 0)
    {
        KITRA_LOG(KITRA_LOG_ERROR, IMG_GetError());
        SDL_FreeSurface(surface);
        return KITRA_STATUS_SCREENSHOT_FAILED;
    }

    SDL_FreeSurface(surface);
    return KITRA_STATUS_OK;
}

KitraSurface *KitraScreenshotSurface(void)
{
    if (!gKitraCtx.core.renderer)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Renderer is NULL in KitraScreenshotSurface");
        return NULL;
    }

    KitraSize size = KitraGetWindowSize();

    SDL_Surface *sdlSurface = SDL_CreateRGBSurfaceWithFormat(
        0, size.w, size.h, 32, SDL_PIXELFORMAT_RGBA32);

    if (!sdlSurface)
    {
        KITRA_LOG(KITRA_LOG_ERROR, SDL_GetError());
        return NULL;
    }

    if (SDL_RenderReadPixels(gKitraCtx.core.renderer, NULL,
                             SDL_PIXELFORMAT_RGBA32,
                             sdlSurface->pixels,
                             sdlSurface->pitch) != 0)
    {
        KITRA_LOG(KITRA_LOG_ERROR, SDL_GetError());
        SDL_FreeSurface(sdlSurface);
        return NULL;
    }

    KitraSurface *surface = KitraSurfaceFromSDL(sdlSurface);
    if (!surface)
    {
        SDL_FreeSurface(sdlSurface);
        return NULL;
    }

    return surface;
}

void KitraDrawTextureEx(KitraTexture *tex, const KitraRect *src, const KitraRect *dst, float angle, const KitraPoint *pivot, KitraFlipFlags flip)
{
    if (!gKitraCtx.core.renderer || !tex)
        return;

    SDL_Rect sdlSrc, sdlDst;
    SDL_Rect *pSrc = NULL, *pDst = NULL;
    SDL_Point sdlPivot, *pPivot = NULL;

    if (src)
    {
        sdlSrc = (SDL_Rect){src->x, src->y, src->w, src->h};
        pSrc = &sdlSrc;
    }

    if (dst)
    {
        sdlDst = (SDL_Rect){dst->x, dst->y, dst->w, dst->h};
        pDst = &sdlDst;
    }

    if (pivot)
    {
        sdlPivot = (SDL_Point){pivot->x, pivot->y};
        pPivot = &sdlPivot;
    }

    switch (flip)
    {
    case KITRA_FLIP_NONE:
        SDL_RenderCopyEx(gKitraCtx.core.renderer, tex->handle, pSrc, pDst, (double)angle, pPivot, (SDL_RendererFlip)SDL_FLIP_NONE);
        break;

    case KITRA_FLIP_VERTICAL:
        SDL_RenderCopyEx(gKitraCtx.core.renderer, tex->handle, pSrc, pDst, (double)angle, pPivot, (SDL_RendererFlip)SDL_FLIP_VERTICAL);
        break;

    case KITRA_FLIP_HORIZONTAL:
        SDL_RenderCopyEx(gKitraCtx.core.renderer, tex->handle, pSrc, pDst, (double)angle, pPivot, (SDL_RendererFlip)SDL_FLIP_HORIZONTAL);
        break;
    }
}

void KitraDrawTexture(KitraTexture *tex, int x, int y)
{
    if (!tex)
        return;

    KitraRect dst = {{x, y, tex->width, tex->height}};
    KitraDrawTextureEx(tex, NULL, &dst, 0.0f, NULL, 0);
}

void KitraDrawTextureP(KitraTexture *tex, KitraPoint pos)
{
    KitraDrawTexture(tex, pos.x, pos.y);
}

SDL_Texture *KitraTextureGetSDL(KitraTexture *tex)
{
    return tex->handle;
}

KitraStatus KitraSetTextureBlendMode(KitraTexture *tex, KitraBlendMode mode)
{
    if (!tex)
        return KITRA_STATUS_TEXTURE_NULL;

    SDL_BlendMode sdlMode;
    switch (mode)
    {
    case KITRA_BLEND_NONE:
        sdlMode = SDL_BLENDMODE_NONE;
        break;
    case KITRA_BLEND_ALPHA:
        sdlMode = SDL_BLENDMODE_BLEND;
        break;
    case KITRA_BLEND_ADDITIVE:
        sdlMode = SDL_BLENDMODE_ADD;
        break;
    case KITRA_BLEND_MULTIPLY:
        sdlMode = SDL_BLENDMODE_MUL;
        break;
    default:
        sdlMode = SDL_BLENDMODE_NONE;
        break;
    }

    SDL_SetTextureBlendMode(tex->handle, sdlMode);
    return KITRA_STATUS_OK;
}

void KitraSetTextureTint(KitraTexture *tex, KitraColor color)
{
    if (!tex)
        return;
    SDL_SetTextureColorMod(tex->handle, color.r, color.g, color.b);
}

void KitraSetTextureAlpha(KitraTexture *tex, uint8_t alpha)
{
    if (!tex)
        return;
    SDL_SetTextureAlphaMod(tex->handle, alpha);
}

KitraTexture *KitraTextureFromSDL(SDL_Texture *tex, int w, int h)
{
    KitraTexture *t = malloc(sizeof(KitraTexture));
    if (!t)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Failed to allocate KitraTexture");
        return NULL;
    }

    t->handle = tex;
    t->width = w;
    t->height = h;
    return t;
}
