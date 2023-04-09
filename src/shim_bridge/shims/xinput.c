#include <stdlib.h>

#include "shims.h"
#include "xinput.h"

static volatile PXInputHook _XInput = NULL;

int SHIMS_CreateXInput(HMODULE hModule, OUT PXInputHook* outHookStruct) {
    _XInput = (PXInputHook)malloc(sizeof(XInputHook));
    
    if (!_XInput) {
        return -1;
    }

    SHIM_INIT(_XInput, XInputGetState);
    SHIM_INIT(_XInput, XInputSetState);
    SHIM_INIT(_XInput, XInputGetCapabilities);
    SHIM_INIT(_XInput, XInputEnable);
    SHIM_INIT(_XInput, XInputGetDSoundAudioDeviceGuids);
    SHIM_INIT(_XInput, XInputGetBatteryInformation);
    SHIM_INIT(_XInput, XInputGetKeystroke);
    
    if (outHookStruct) {
        *outHookStruct = _XInput;
    }
    
    return 0;
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