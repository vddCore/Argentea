#include <iostream>
#include <filesystem>

#include <windows.h>

#include <monochrome.h>

#include "mono/Mono.h"
#include "mono/MonoDomain.h"
#include "mono/MonoAssembly.h"
#include "mono/MonoClass.h"

namespace fs = std::filesystem;

using namespace std;
using namespace MonoChrome;

MONOCHROME_CAPI BOOL MONOCHROME_INITIALIZER_NAME(const char* appBaseDirectory) {
    fs::path appBasePath(appBaseDirectory);
    
    fs::path monochromeAssemblyPath(appBasePath);
    monochromeAssemblyPath /= "monochrome/MonoChrome.dll";
    
    cout << "Initializing Mono subsystem..." << endl;
    auto rootDomain = Mono::Initialize(appBasePath, "MonoChrome");
    cout << " -> Success: " << rootDomain->getName() << endl;
    
    cout << "Loading " << monochromeAssemblyPath.string() << "..." << endl;
    auto assembly = rootDomain->LoadAssembly(monochromeAssemblyPath);
    cout << " -> Found: " << assembly->getFullName() << endl;
    
    cout << "Looking for MonoChrome.Core class..." << endl;
    auto coreClass = assembly->FindClass("MonoChrome", "Core");
    cout << " -> Found: " << coreClass->getNameSpace() << "." << coreClass->getName() << endl;
    
    cout << "Awaiting UE4 initialization.";
    return TRUE;
}