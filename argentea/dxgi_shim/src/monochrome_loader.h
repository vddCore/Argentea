#ifndef ARGENTEA_MONOCHROME_LOADER_H
#define ARGENTEA_MONOCHROME_LOADER_H

#include <windows.h>
#include "shim_context.h"

BOOL MonochromeLoader_Initialize(PShimContext context);
BOOL MonochromeLoader_Invoke(PShimContext context);

#endif //ARGENTEA_MONOCHROME_LOADER_H
