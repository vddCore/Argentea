#ifndef ARGENTEA_XINPUT_H
#define ARGENTEA_XINPUT_H

#include <windows.h>

typedef DWORD(WINAPI* PXInputGetState)(
    DWORD dwUserIndex,
    void* pState
);

typedef DWORD(WINAPI* PXInputSetState)(
    DWORD dwUserIndex,
    void* pVibration
);

typedef DWORD(WINAPI* PXInputGetCapabilities)(
    DWORD dwUserIndex,
    DWORD dwFlags,
    void* pCapabilities
);

typedef void(WINAPI* PXInputEnable)(
    BOOL enable
);

typedef DWORD(WINAPI* PXInputGetDSoundAudioDeviceGuids)(
    DWORD dwUserIndex,
    GUID* pDSoundRenderGuid,
    GUID* pDSoundCaptureGuid
);

typedef DWORD(WINAPI* PXInputGetBatteryInformation)(
    DWORD dwUserIndex,
    BYTE devType,
    void* pBatteryInformation
);

typedef DWORD(WINAPI* PXInputGetKeystroke)(
    DWORD dwUserIndex,
    DWORD dwReserved,
    void* pKeystroke
);

typedef struct _XInputHook {
    PXInputGetState XInputGetState;
    PXInputSetState XInputSetState;
    PXInputGetCapabilities XInputGetCapabilities;
    PXInputEnable XInputEnable;
    PXInputGetDSoundAudioDeviceGuids XInputGetDSoundAudioDeviceGuids;
    PXInputGetBatteryInformation XInputGetBatteryInformation;
    PXInputGetKeystroke XInputGetKeystroke;
} XInputHook, *PXInputHook;

#endif //ARGENTEA_XINPUT_H
