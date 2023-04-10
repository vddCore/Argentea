#ifndef ARGENTEA_SHIM_CONTEXT_H
#define ARGENTEA_SHIM_CONTEXT_H

#include <windows.h>

#include <monochrome.h>

#include "shims/shims.h"

typedef struct _ShimContext {
    DWORD parentProcessId;
    HINSTANCE thisModuleHandle;
    
    HMODULE monochromeModuleHandle;
    PMonochromeInitializer monochromeInitializer;
    
    WCHAR thisModulePath[MAX_PATH];
    WCHAR appBaseDirectoryPath[MAX_PATH];
    WCHAR systemDirectoryPath[MAX_PATH];
} ShimContext, *PShimContext;

PShimContext ShimContext_Create(void);
void ShimContext_Destroy(PShimContext context);

#endif //ARGENTEA_SHIM_CONTEXT_H
