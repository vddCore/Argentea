#include <stdlib.h>

#include "shims.h"
#include "dinput8.h"

static volatile PDInput8Hook _DInput8 = NULL;

Shim_CreationResult Shim_CreateDInput8(HMODULE hModule, OUT PDInput8Hook* outHookStruct) {
    _DInput8 = (PDInput8Hook)malloc(sizeof(DInput8Hook));

    if (!_DInput8) {
        return SHIM_OUT_OF_MEMORY;
    }
    
    memset(_DInput8, 0, sizeof(DInput8Hook));

    SHIM_INIT_OR_QUIT(_DInput8, DirectInput8Create);
    
    if (outHookStruct) {
        *outHookStruct = _DInput8;
    }

    return SHIM_OK;
}

void Shim_DestroyDInput8(void) {
    HOOK_DESTROY(_DInput8);
}

SHIM HRESULT WINAPI DirectInput8Create(
    HINSTANCE hinst,
    DWORD dwVersion,
    REFIID riidltf,
    LPVOID* ppvOut,
    void* punkOuter
) {
    return _DInput8->DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
}