#include <stdlib.h>

#include "shims.h"
#include "xinput.h"

static volatile PXInputHook _XInput = NULL;

ShimCreateResult SHIMS_CreateXInput(HMODULE hModule, OUT PXInputHook* outHookStruct) {
    _XInput = (PXInputHook)malloc(sizeof(XInputHook));
    
    if (!_XInput) {
        return SHIM_OUT_OF_MEMORY;
    }
    
    memset(_XInput, 0, sizeof(XInputHook));

    SHIM_INIT_OR_QUIT(_XInput, XInputGetState);
    SHIM_INIT_OR_QUIT(_XInput, XInputSetState);
    SHIM_INIT_OR_QUIT(_XInput, XInputGetCapabilities);
    SHIM_INIT_OR_QUIT(_XInput, XInputEnable);
    SHIM_INIT_OR_QUIT(_XInput, XInputGetDSoundAudioDeviceGuids);
    SHIM_INIT_OR_QUIT(_XInput, XInputGetBatteryInformation);
    SHIM_INIT_OR_QUIT(_XInput, XInputGetKeystroke);
    
    if (outHookStruct) {
        *outHookStruct = _XInput;
    }
    
    return SHIM_OK;
}

void SHIMS_DestroyXInput(void) {
    HOOK_DESTROY(_XInput);
}

SHIM void WINAPI XInput_Ordinal1_Stub() {
}

SHIM DWORD WINAPI XInputGetState(DWORD dwUserIndex, void* pState) {
    return _XInput->XInputGetState(dwUserIndex, pState);
}

SHIM DWORD WINAPI XInputSetState(DWORD dwUserIndex, void* pVibration) {
    return _XInput->XInputSetState(dwUserIndex, pVibration);
}

SHIM DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, void* pCapabilities) {
    return _XInput->XInputGetCapabilities(dwUserIndex, dwFlags, pCapabilities);
}

SHIM void WINAPI XInputEnable(BOOL enable) {
    _XInput->XInputEnable(enable);
}

SHIM DWORD WINAPI XInputGetDSoundAudioDeviceGuids(
    DWORD dwUserIndex,
    GUID* pDSoundRenderGuid,
    GUID* pDSoundCaptureGuid
) {
    return _XInput->XInputGetDSoundAudioDeviceGuids(
        dwUserIndex,
        pDSoundRenderGuid,
        pDSoundCaptureGuid
    );    
}

SHIM DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, void* pBatteryInformation) {
    return _XInput->XInputGetBatteryInformation(dwUserIndex, devType, pBatteryInformation);
}

SHIM DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, void* pKeystroke) {
    return _XInput->XInputGetKeystroke(dwUserIndex, dwReserved, pKeystroke);
}