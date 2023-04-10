#include <iostream>

#include <windows.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <monochrome.h>

using namespace std;

MONOCHROME_CAPI BOOL MONOCHROME_INITIALIZER_NAME(const char* appBaseDirectory) {
    string appBaseString(appBaseDirectory);
    cout << "MonoChrome says hello, C++ world: " << appBaseString << endl;
    
    return TRUE;
}