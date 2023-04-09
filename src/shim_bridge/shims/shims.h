#ifndef ARGENTEA_SHIMS_H
#define ARGENTEA_SHIMS_H

#include <Windows.h>

#include "dinput8.h"
#include "dxgi.h"
#include "x3daudio.h"
#include "xinput.h"

#define SHIM __declspec(dllexport)

#define SHIM_INIT(x, y)                      \
  x->y = (P ## y)GetProcAddress(hModule, #y) \

#define HOOK_DESTROY(x) \
  if (x) {              \
    free(x);            \
    x = NULL;           \
  }

int SHIMS_CreateDInput8(HMODULE hModule, OUT PDInput8Hook* outHookStruct);
int SHIMS_CreateDXGI(HMODULE hModule, OUT PDXGIHook* outHookStruct);
int SHIMS_CreateX3DAudio(HMODULE hModule, OUT PX3DAudioHook* outHookStruct);
int SHIMS_CreateXInput(HMODULE hModule, OUT PXInputHook* outHookStruct);

void SHIMS_DestroyDInput8(void);
void SHIMS_DestroyDXGI(void);
void SHIMS_DestroyX3DAudio(void);
void SHIMS_DestroyXInput(void);

#endif //ARGENTEA_SHIMS_H
