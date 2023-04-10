#ifndef ARGENTEA_SHIM_LIFECYCLE_H
#define ARGENTEA_SHIM_LIFECYCLE_H

#include <windows.h>

#include "shim_context.h"

void ShimLifecycle_Attach(PShimContext context);
void ShimLifecycle_Detach(PShimContext context);

#endif //ARGENTEA_SHIM_LIFECYCLE_H