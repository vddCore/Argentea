#include <locale.h>

/* Required to select target architecture. */
#include <windows.h>
#include <processthreadsapi.h>

#include "lifecycle.h"
#include "shim_bridge.h"

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