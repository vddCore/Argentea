#include <locale.h>
#include <stdio.h>

/* Required to select target architecture. */
#include <windows.h>
#include <shlwapi.h>
#include <strsafe.h>
#include <processthreadsapi.h>

#include "shim_context.h"
#include "shim_lifecycle.h"
#include "shim_bridge.h"
#include "monochrome_loader.h"

static volatile PShimContext _CurrentShimContext;

BOOL ResolveContextPaths(PShimContext context) {
    if (!context) {
        return FALSE;
    }

    if (!GetSystemDirectoryW(
        context->systemDirectoryPath,
        sizeof(context->systemDirectoryPath))
    ) return FALSE;

    if (!GetModuleFileNameW(
        context->thisModuleHandle,
        context->thisModulePath,
        sizeof(context->thisModulePath))
    ) return FALSE;

    StringCchCopyW(
        context->appBaseDirectoryPath,
        sizeof(context->appBaseDirectoryPath),
        context->thisModulePath
    );

    if (!PathRemoveFileSpecW(context->appBaseDirectoryPath)) {
        return FALSE;
    }

    return TRUE;
}

PShimContext InitializeShimContext(HINSTANCE hInstDLL, DWORD dwProcessId) {
    PShimContext context = ShimContext_Create();

    if (context) {
        context->thisModuleHandle = hInstDLL;
        context->parentProcessId = dwProcessId;

        if (!ResolveContextPaths(context)) {
            goto __error;
        }

        if (!MonochromeLoader_Initialize(context)) {
            goto __error;
        }
    }

    return context;

__error:
    free(context);
    context = NULL;

    return context;
}

BOOL Attach(HINSTANCE hInstDLL) {
    _CurrentShimContext = InitializeShimContext(
        hInstDLL,
        GetCurrentProcessId()
    );

    if (_CurrentShimContext) {
        ShimLifecycle_Attach(_CurrentShimContext);
        ShimBridge_Create(_CurrentShimContext);
    }

    return (BOOL)(_CurrentShimContext != NULL);
}

void Detach(void) {
    if (_CurrentShimContext) {
        ShimBridge_Destroy();
        ShimLifecycle_Detach(_CurrentShimContext);
        ShimContext_Destroy(_CurrentShimContext);
    }
}

void Begin(HINSTANCE hInstDLL) {
    BOOL result = Attach(hInstDLL);

    if (result) {
        MonochromeLoader_Invoke(_CurrentShimContext);
    }
}

BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    setlocale(LC_ALL, "C.UTF-8");

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH: {
            CloseHandle(
                CreateThread(
                    NULL,
                    0,
                    (LPTHREAD_START_ROUTINE)Begin,
                    hInstDLL,
                    0,
                    NULL
                )
            );
            break;
        }

        case DLL_PROCESS_DETACH:
            Detach();
            break;

        default:
            /* Ignore request, not something we care about. */
            break;
    }

    return TRUE;
}