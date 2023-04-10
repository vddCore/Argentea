#ifndef ARGENTEA_SHIMS_H
#define ARGENTEA_SHIMS_H

#include <Windows.h>

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
} ShimCreateResult;

ShimCreateResult SHIMS_CreateDInput8(
    HMODULE hModule,
    OUT PDInput8Hook* outHookStruct
);

ShimCreateResult SHIMS_CreateDXGI(
    HMODULE hModule,
    OUT PDXGIHook* outHookStruct
);

ShimCreateResult SHIMS_CreateX3DAudio(
    HMODULE hModule,
    OUT PX3DAudioHook* outHookStruct
);

ShimCreateResult SHIMS_CreateXInput(
    HMODULE hModule,
    OUT PXInputHook* outHookStruct
);

void SHIMS_DestroyDInput8(void);
void SHIMS_DestroyDXGI(void);
void SHIMS_DestroyX3DAudio(void);
void SHIMS_DestroyXInput(void);

#endif //ARGENTEA_SHIMS_H
