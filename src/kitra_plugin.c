#include "kitra_internal.h"

KitraPluginHandle KitraRegisterPlugin(KitraPlugin plugin, KitraStatus *status)
{
#define RETURN_ERR(code)                    \
    do                                      \
    {                                       \
        if (status)                         \
            *status = (code);               \
        return KITRA_PLUGIN_HANDLE_INVALID; \
    } while (0)

    if (gKitraCtx.pluginCount >= KITRA_MAX_PLUGINS)
    {
        KITRA_LOG(KITRA_LOG_ERROR, "Maximum plugin count reached");
        RETURN_ERR(KITRA_STATUS_PLUGIN_MAX_REACHED);
    }

    /* Pop a free slot index off the free list stack */
    uint16_t slotIndex = gKitraCtx.pluginFreeList[gKitraCtx.pluginFreeHead];
    gKitraCtx.pluginFreeHead++;

    KitraPluginSlot *slot = &gKitraCtx.pluginSlots[slotIndex];

    /* Place the new plugin at the end of the dense array and link it back
       to its slot so that swap-with-last removal can find the slot later */
    uint16_t denseIndex = (uint16_t)gKitraCtx.pluginCount;
    gKitraCtx.pluginDense[denseIndex].plugin = plugin;
    gKitraCtx.pluginDense[denseIndex].slotIndex = slotIndex;
    slot->denseIndex = denseIndex;

    /* Issue the handle before calling init so the caller has a valid handle
       even if init triggers further engine operations */
    KitraPluginHandle handle = {
        .index = slotIndex,
        .generation = slot->generation,
    };

    gKitraCtx.pluginCount++;

    if (plugin.init)
        plugin.init(plugin.userdata);

    if (status)
        *status = KITRA_STATUS_OK;
    return handle;

#undef RETURN_ERR
}

KitraStatus KitraUnregisterPlugin(KitraPluginHandle handle)
{
    if (!KitraPluginHandleIsValid(handle))
        return KITRA_STATUS_PLUGIN_INVALID_HANDLE;

    uint16_t slotIndex = handle.index;

    if (slotIndex >= KITRA_MAX_PLUGINS)
        return KITRA_STATUS_PLUGIN_INVALID_HANDLE;

    KitraPluginSlot *slot = &gKitraCtx.pluginSlots[slotIndex];

    if (slot->generation != handle.generation)
    {
        KITRA_LOG(KITRA_LOG_WARNING, "KitraUnregisterPlugin: stale handle");
        return KITRA_STATUS_PLUGIN_INVALID_HANDLE;
    }

    uint16_t denseIndex = slot->denseIndex;
    KitraPlugin *plugin = &gKitraCtx.pluginDense[denseIndex].plugin;

    if (plugin->shutdown)
        plugin->shutdown(plugin->userdata);

    /* Bump generation to permanently invalidate all existing handle copies */
    slot->generation++;

    /* O(1) removal: overwrite the target with the last dense entry */
    uint16_t lastDense = (uint16_t)(gKitraCtx.pluginCount - 1);

    if (denseIndex != lastDense)
    {
        gKitraCtx.pluginDense[denseIndex] = gKitraCtx.pluginDense[lastDense];

        /* Update the moved plugin's slot so its handle still resolves correctly */
        uint16_t movedSlot = gKitraCtx.pluginDense[denseIndex].slotIndex;
        gKitraCtx.pluginSlots[movedSlot].denseIndex = denseIndex;
    }

    gKitraCtx.pluginCount--;

    /* Return the slot to the free list stack */
    gKitraCtx.pluginFreeHead--;
    gKitraCtx.pluginFreeList[gKitraCtx.pluginFreeHead] = slotIndex;

    return KITRA_STATUS_OK;
}