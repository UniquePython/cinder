#include "kitra_internal.h"

bool KitraIsRunning(void)
{
    return gKitraCtx.loop.isRunning;
}

void KitraRequestQuit(void)
{
    gKitraCtx.loop.isRunning = false;
}

void KitraBeginFrame(void)
{
    // ---------------- Delta time ----------------

    uint64_t now = SDL_GetPerformanceCounter();

    gKitraCtx.timing.deltaTime = (gKitraCtx.timing.lastCounter == 0)
                                     ? 0.0f
                                     : (float)(now - gKitraCtx.timing.lastCounter) / (float)gKitraCtx.timing.perfFrequency;

    gKitraCtx.timing.lastCounter = now;

    if (gKitraCtx.timing.deltaTime > 0.0f)
    {
        float instantFPS = 1.0f / gKitraCtx.timing.deltaTime;
        const float alpha = 0.1f;

        gKitraCtx.timing.fps = (gKitraCtx.timing.fps == 0.0f)
                                   ? instantFPS
                                   : alpha * instantFPS + (1.0f - alpha) * gKitraCtx.timing.fps;
    }

    // ---------------- Reset per-frame input ----------------

    memset(gKitraCtx.input.keyboard.pressed, 0, sizeof(gKitraCtx.input.keyboard.pressed));
    memset(gKitraCtx.input.keyboard.released, 0, sizeof(gKitraCtx.input.keyboard.released));
    memset(gKitraCtx.input.mouse.pressed, 0, sizeof(gKitraCtx.input.mouse.pressed));
    memset(gKitraCtx.input.mouse.released, 0, sizeof(gKitraCtx.input.mouse.released));

    gKitraCtx.input.mouse.delta = (KitraVec2i){{0, 0}};
    gKitraCtx.input.mouse.scrollDelta = (KitraVec2i){{0, 0}};
    gKitraCtx.input.mouse.prevPos = gKitraCtx.input.mouse.pos;
    gKitraCtx.loop.frameBegun = true;
    gKitraCtx.loop.resized = false;

    // ---------------- Event processing ----------------

    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent))
    {
        if (sdlEvent.type == SDL_QUIT)
            KitraRequestQuit();
        else
            KitraInputProcessEvent(&sdlEvent);
    }

    // ---------------- Plugin callbacks ----------------

    for (int i = 0; i < gKitraCtx.pluginCount; i++)
    {
        KitraPlugin *p = &gKitraCtx.pluginDense[i].plugin;
        if (p->update)
            p->update(gKitraCtx.timing.deltaTime, p->userdata);
    }
}

void KitraEndFrame(void)
{
    if (!gKitraCtx.loop.frameBegun)
    {
        KITRA_LOG(KITRA_LOG_WARNING, "KitraEndFrame called without KitraBeginFrame");
        return;
    }

    gKitraCtx.loop.frameBegun = false;

    for (int i = 0; i < gKitraCtx.pluginCount; i++)
    {
        KitraPlugin *p = &gKitraCtx.pluginDense[i].plugin;
        if (p->draw)
            p->draw(p->userdata);
    }

    if (gKitraCtx.timing.targetFPS > 0)
    {
        double frameTimeSec =
            (double)(SDL_GetPerformanceCounter() - gKitraCtx.timing.lastCounter) /
            (double)gKitraCtx.timing.perfFrequency;

        double targetFrameTime = 1.0 / (double)gKitraCtx.timing.targetFPS;

        if (frameTimeSec < targetFrameTime)
            SDL_Delay((Uint32)((targetFrameTime - frameTimeSec) * 1000.0));
    }

    if (gKitraCtx.core.renderer)
        SDL_RenderPresent(gKitraCtx.core.renderer);
    else
        KITRA_LOG(KITRA_LOG_WARNING, "Renderer is NULL in KitraEndFrame");
}