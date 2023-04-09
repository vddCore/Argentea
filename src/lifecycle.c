#include <stdio.h>
#include "lifecycle.h"

void _LC_CreateDebugConsole() {
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void LC_Attach(DWORD dwProcessId) {
    _LC_CreateDebugConsole();
    printf("%s\n", "Hello, world!!");
}

void LC_Detach(void) {
    printf("%s\n", "Goodbye, world.");
    FreeConsole();
}
