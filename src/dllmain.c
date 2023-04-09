#include <stdio.h>
#include <Windows.h>
#include <processthreadsapi.h>

#include <locale.h>

#include "lifecycle.h"
#include "shim_bridge/shim_bridge.h"

BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    setlocale(LC_ALL, "C.UTF-8");
    
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            LC_Attach(GetCurrentProcessId());
            SB_Create(hInstDLL);
            break;
        
        case DLL_PROCESS_DETACH:
            SB_Destroy();
            LC_Detach();
            break;
        
        default:
            /* Ignore request, not something we care about. */
            break;
    }
    
    return TRUE;
}