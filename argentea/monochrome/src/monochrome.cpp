#include <iostream>

#include <windows.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <monochrome.h>

MONOCHROME_CAPI void MONOCHROME_INITIALIZER_NAME(const WCHAR* appBaseDirectory) {
    std::cout << "MonoChrome says hello, C++ world." << std::endl;
}