#ifndef ARGENTEA_SHIM_BRIDGE_H
#define ARGENTEA_SHIM_BRIDGE_H

#include <windows.h>

int ShimBridge_Create(HINSTANCE hDllInstance);
void ShimBridge_Destroy(void);

#endif //ARGENTEA_SHIM_BRIDGE_H
