#ifndef ARGENTEA_SHIMS_H
#define ARGENTEA_SHIMS_H

#include <windows.h>

#include "dinput8.h"
#include "dxgi.h"
#include "x3daudio.h"
#include "xinput.h"

#define SHIM __declspec(dllexport)

#define SHIM_INIT_OR_QUIT(x, y)               \
  x->y = (P ## y)GetProcAddress(hModule, #y); \
  if (!(x->y)) return SHIM_FUNCTION_MISSING   \

#define HOOK_DESTROY(x) \
  if (x) {              \
    free(x);            \
    x = NULL;           \
  }                     \

typedef enum _ShimCreateResult {
    SHIM_OK = 0,
    SHIM_OUT_OF_MEMORY = -1,
    SHIM_FUNCTION_MISSING = -2
} Shim_CreationResult;

Shim_CreationResult Shim_CreateDInput8(
    HMODULE hModule,
    OUT PDInput8Hook* outHookStruct
);

Shim_CreationResult Shim_CreateDXGI(
    HMODULE hModule,
    OUT PDXGIHook* outHookStruct
);

Shim_CreationResult Shim_CreateX3DAudio(
    HMODULE hModule,
    OUT PX3DAudioHook* outHookStruct
);

Shim_CreationResult Shim_CreateXInput(
    HMODULE hModule,
    OUT PXInputHook* outHookStruct
);

void Shim_DestroyDInput8(void);
void Shim_DestroyDXGI(void);
void Shim_DestroyX3DAudio(void);
void Shim_DestroyXInput(void);

#endif //ARGENTEA_SHIMS_H
