#ifndef ARGENTEA_MONOCHROME_H
#define ARGENTEA_MONOCHROME_H

#include <windows.h>

#define MONOCHROME_CAPI extern "C" __declspec(dllexport)
#define MONOCHROME_INITIALIZER_NAME Monochrome_Initialize
#define MONOCHROME_INITIALIZER_NAMESTRING "Monochrome_Initialize"

typedef BOOL (*PMonochromeInitializer)(const char* appBaseDirectory);

#endif //ARGENTEA_MONOCHROME_H
