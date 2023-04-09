#include <stdio.h>
#include <stdlib.h>

#include <shlwapi.h>

#include "shim_bridge.h"
#include "shims/shims.h"

int SB_Create(HINSTANCE hDllInstance) {
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

    SHIMS_CreateDInput8(originalModuleHandle, NULL);
    SHIMS_CreateDXGI(originalModuleHandle, NULL);
    SHIMS_CreateX3DAudio(originalModuleHandle, NULL);
    SHIMS_CreateXInput(originalModuleHandle, NULL);

    return 0;
}

void SB_Destroy(void) {
    SHIMS_DestroyDInput8();
    SHIMS_DestroyDXGI();
    SHIMS_DestroyX3DAudio();
    SHIMS_DestroyXInput();
}