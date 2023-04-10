#ifndef ARGENTEA_MONOCHROME_H
#define ARGENTEA_MONOCHROME_H

#include <windows.h>

#define MONOCHROME_CAPI extern "C" __declspec(dllexport)
#define MONOCHROME_INITIALIZER_NAME Monochrome_Initialize

typedef void (*PMonochromeInitializer)(const WCHAR* appBaseDirectory);

#endif //ARGENTEA_MONOCHROME_H
