#include <stdio.h>

#include <Shlwapi.h>

#include "shim_bridge.h"
#include "shims/shims.h"

int ShimBridge_Create(PShimContext context) {
    if (!context) {
        return -1;
    }

    LPWSTR thisModuleFileName = PathFindFileNameW(context->thisModulePath);
    if (!thisModuleFileName) {
        return -1;
    }

    WCHAR impersonatedModulePath[MAX_PATH] = {0};
    PathCombineW(
        impersonatedModulePath,
        context->systemDirectoryPath,
        thisModuleFileName
    );

    HMODULE originalModuleHandle = LoadLibraryW(impersonatedModulePath);
    if (!originalModuleHandle) {
        return -1;
    }

    Shim_CreateDInput8(originalModuleHandle, NULL);
    Shim_CreateDXGI(originalModuleHandle, NULL);
    Shim_CreateX3DAudio(originalModuleHandle, NULL);
    Shim_CreateXInput(originalModuleHandle, NULL);

    return 0;
}

void ShimBridge_Destroy(void) {
    Shim_DestroyDInput8();
    Shim_DestroyDXGI();
    Shim_DestroyX3DAudio();
    Shim_DestroyXInput();
}