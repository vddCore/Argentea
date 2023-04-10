#ifndef ARGENTEA_SHIM_BRIDGE_H
#define ARGENTEA_SHIM_BRIDGE_H

#include <windows.h>

#include "shim_context.h"

int ShimBridge_Create(PShimContext context);
void ShimBridge_Destroy(void);

#endif //ARGENTEA_SHIM_BRIDGE_H
