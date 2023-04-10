#ifndef ARGENTEA_SHIM_LIFECYCLE_H
#define ARGENTEA_SHIM_LIFECYCLE_H

#include <windows.h>

void ShimLifecycle_Attach(DWORD dwProcessId);
void ShimLifecycle_Detach(void);

#endif //ARGENTEA_SHIM_LIFECYCLE_H