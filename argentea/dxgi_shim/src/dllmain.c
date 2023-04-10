#include <locale.h>
#include <stdio.h>

/* Required to select target architecture. */
#include <windows.h>
#include <processthreadsapi.h>

#include <monochrome.h>

#include "shim_lifecycle.h"
#include "shim_bridge.h"

BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    setlocale(LC_ALL, "C.UTF-8");

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            ShimBridge_Create(hInstDLL);
            ShimLifecycle_Attach(GetCurrentProcessId());
            break;

        case DLL_PROCESS_DETACH:
            ShimLifecycle_Detach();
            ShimBridge_Destroy();
            break;

        default:
            /* Ignore request, not something we care about. */
            break;
    }

    return TRUE;
}