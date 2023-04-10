#include <shlwapi.h>

#include <monochrome.h>

#include "monochrome_loader.h"

BOOL MonochromeLoader_Initialize(PShimContext context) {
    if (!context) {
        return FALSE;
    }

    WCHAR monochromeLibraryPath[MAX_PATH] = {0};
    PathCombineW(
        monochromeLibraryPath,
        context->appBaseDirectoryPath,
        L"monochrome.dll"
    );

    context->monochromeModuleHandle = LoadLibraryW(monochromeLibraryPath);
    if (!context->monochromeModuleHandle) {
        return FALSE;
    }

    context->monochromeInitializer = (PMonochromeInitializer)GetProcAddress(
        context->monochromeModuleHandle,
        MONOCHROME_INITIALIZER_NAMESTRING
    );
    if (!context->monochromeInitializer) {
        return FALSE;
    }

    return TRUE;
}

BOOL MonochromeLoader_Invoke(PShimContext context) {
    if (!context) {
        return FALSE;
    }
    
    if (!context->monochromeInitializer) {
        return FALSE;
    }
    
    char appBaseDirectoryMultiByte[MAX_PATH * 2] = {0};
    char defaultChar = ' ';
    WideCharToMultiByte(
        CP_UTF8, 
        0,
        context->appBaseDirectoryPath,
        sizeof(context->appBaseDirectoryPath),
        appBaseDirectoryMultiByte,
        sizeof(appBaseDirectoryMultiByte),
        &defaultChar,
        NULL
    );
    
    return context->monochromeInitializer(appBaseDirectoryMultiByte);
}