#include "kitra_internal.h"

KitraCtx gKitraCtx;

static void KitraRollbackSubsystems(uint32_t flags)
{
    if (flags & SDL_INIT_VIDEO)
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    if (flags & SDL_INIT_AUDIO)
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    if (flags & SDL_INIT_EVENTS)
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

KitraStatus KitraInit(KitraSubsystem flags)
{
    if (gKitraCtx.core.initFlags != 0)
        return KITRA_STATUS_SUBSYSTEM_DOUBLE_INIT;

    gKitraCtx = (KitraCtx){0};

    for (int i = 0; i < KITRA_MAX_PLUGINS; i++)
        gKitraCtx.pluginFreeList[i] = (uint16_t)(KITRA_MAX_PLUGINS - 1 - i);
    gKitraCtx.pluginFreeHead = 0;

    gKitraCtx.timing.perfFrequency = SDL_GetPerformanceFrequency();

    KitraInputInit();
    KitraRngSeedAuto(&gKitraCtx.rng);

    if (!gKitraCtx.log.callback)
        KitraSetErrorCallback(KitraDefaultLogCallback, NULL);

    if (flags & KITRA_SUBSYSTEM_EVENTS)
    {
        if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
        {
            KITRA_LOG(KITRA_LOG_ERROR, "Failed to initialize EVENTS subsystem");
            KitraRollbackSubsystems(gKitraCtx.core.initFlags);
            gKitraCtx.core.initFlags = 0;
            return KITRA_STATUS_SUBSYSTEM_INIT_FAILED;
        }
        gKitraCtx.core.initFlags |= SDL_INIT_EVENTS;
    }

    if (flags & KITRA_SUBSYSTEM_AUDIO)
    {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
        {
            KITRA_LOG(KITRA_LOG_ERROR, "Failed to initialize AUDIO subsystem");
            KitraRollbackSubsystems(gKitraCtx.core.initFlags);
            gKitraCtx.core.initFlags = 0;
            return KITRA_STATUS_SUBSYSTEM_INIT_FAILED;
        }
        gKitraCtx.core.initFlags |= SDL_INIT_AUDIO;

        int mixFlags = MIX_INIT_OGG;
        if ((Mix_Init(mixFlags) & mixFlags) != mixFlags)
        {
            KITRA_LOG(KITRA_LOG_ERROR, Mix_GetError());
            KitraRollbackSubsystems(gKitraCtx.core.initFlags);
            gKitraCtx.core.initFlags = 0;
            return KITRA_STATUS_SUBSYSTEM_INIT_FAILED;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            KITRA_LOG(KITRA_LOG_ERROR, Mix_GetError());
            Mix_Quit();
            KitraRollbackSubsystems(gKitraCtx.core.initFlags);
            gKitraCtx.core.initFlags = 0;
            return KITRA_STATUS_SUBSYSTEM_INIT_FAILED;
        }

        gKitraCtx.core.audioInitialized = true;
    }

    if (flags & KITRA_SUBSYSTEM_VIDEO)
    {
        if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
        {
            KITRA_LOG(KITRA_LOG_ERROR, "Failed to initialize VIDEO subsystem");
            KitraRollbackSubsystems(gKitraCtx.core.initFlags);
            gKitraCtx.core.initFlags = 0;
            return KITRA_STATUS_SUBSYSTEM_INIT_FAILED;
        }
        gKitraCtx.core.initFlags |= SDL_INIT_VIDEO;
    }

    return KITRA_STATUS_OK;
}

void KitraQuit(void)
{
    for (int i = 0; i < gKitraCtx.pluginCount; i++)
    {
        KitraPlugin *p = &gKitraCtx.pluginDense[i].plugin;
        if (p->shutdown)
            p->shutdown(p->userdata);
    }

    KitraDestroyWindow();

    gKitraCtx.core.initFlags = 0;

    if (gKitraCtx.core.imgInitialized)
        IMG_Quit();
    if (gKitraCtx.core.ttfInitialized)
        TTF_Quit();
    if (gKitraCtx.core.audioInitialized)
    {
        Mix_CloseAudio();
        Mix_Quit();
    }

    SDL_Quit();
}
