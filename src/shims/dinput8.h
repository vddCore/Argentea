#ifndef ARGENTEA_DINPUT8_H
#define ARGENTEA_DINPUT8_H

#include <Windows.h>

typedef HRESULT(WINAPI* PDirectInput8Create)(
    HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID* ppvOut,
    void* punkOuter
);

typedef struct _DInput8Hook {
    PDirectInput8Create DirectInput8Create;
} DInput8Hook, *PDInput8Hook;

#endif //ARGENTEA_DINPUT8_H
