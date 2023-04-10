#include <stdio.h>

#include <Shlwapi.h>

#include "shim_bridge.h"
#include "shims/shims.h"

int ShimBridge_Create(HINSTANCE hDllInstance) {
    WCHAR systemDirectoryPath[MAX_PATH] = {0};
    if (!GetSystemDirectoryW(systemDirectoryPath, sizeof(systemDirectoryPath))) {
        return -1;
    }

    WCHAR thisModulePath[MAX_PATH] = {0};
    if (!GetModuleFileNameW(hDllInstance, thisModulePath, sizeof(thisModulePath))) {
        return -1;
    }

    LPWSTR thisModuleFileName = PathFindFileNameW(thisModulePath);
    if (!thisModuleFileName) {
        return -1;
    }

    WCHAR completeModulePath[MAX_PATH] = {0};
    PathCombineW(completeModulePath, systemDirectoryPath, thisModuleFileName);

    HMODULE originalModuleHandle = LoadLibraryW(completeModulePath);
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