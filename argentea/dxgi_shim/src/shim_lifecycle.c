#include <stdio.h>

#include "shim_lifecycle.h"

void _CreateDebugConsole(void) {
    AllocConsole();
    
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void _DestroyDebugConsole(void) {
    FreeConsole();
}

void ShimLifecycle_Attach(DWORD dwProcessId) {
    _CreateDebugConsole();
}

void ShimLifecycle_Detach(void) {
    _DestroyDebugConsole();
}
