#ifndef ARGENTEA_X3DAUDIO_H
#define ARGENTEA_X3DAUDIO_H

#include <Windows.h>

typedef DWORD(WINAPI* PX3DAudioInitialize)(
    UINT32 SpeakerChannelMask,
    float SpeedOfSound,
    void* Instance
);

typedef DWORD(WINAPI* PX3DAudioCalculate)(
    void* Instance,
    void* pListener,
    void* pEmitter,
    UINT32 Flags,
    void* pDSPSettings
);

typedef struct _X3DAudioHook {
    PX3DAudioInitialize X3DAudioInitialize;
    PX3DAudioCalculate X3DAudioCalculate;
} X3DAudioHook, *PX3DAudioHook;

#endif
