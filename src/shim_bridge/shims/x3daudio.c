#include <stdlib.h>

#include "shims.h"
#include "x3daudio.h"

static volatile PX3DAudioHook _X3DAudio = NULL;

int SHIMS_CreateX3DAudio(HMODULE hModule, OUT PX3DAudioHook* outHookStruct) {
    _X3DAudio = (PX3DAudioHook)malloc(sizeof(X3DAudioHook));

    if (!_X3DAudio) {
        return -1;
    }

    SHIM_INIT(_X3DAudio, X3DAudioInitialize);
    SHIM_INIT(_X3DAudio, X3DAudioCalculate);
    
    if (outHookStruct) {
        *outHookStruct = _X3DAudio;
    }
    
    return 0;
}

void SHIMS_DestroyX3DAudio(void) {
    HOOK_DESTROY(_X3DAudio);
}

SHIM DWORD WINAPI X3DAudioInitialize(UINT32 SpeakerChannelMask, float SpeedOfSound, void* Instance) {
    return _X3DAudio->X3DAudioInitialize(SpeakerChannelMask, SpeedOfSound, Instance);
}

SHIM DWORD WINAPI X3DAudioCalculate(
    void* Instance,
    void* pListener,
    void* pEmitter,
    UINT32 Flags,
    void* pDSPSettings
) {
    return _X3DAudio->X3DAudioCalculate(Instance, pListener, pEmitter, Flags, pDSPSettings);
}