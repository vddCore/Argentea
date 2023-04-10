#include <iostream>
#include <filesystem>

#include <windows.h>

#include <mono/jit/jit.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/object.h>
#include <mono/metadata/debug-helpers.h>

#include <monochrome.h>
#include "mono/metadata/threads.h"

namespace fs = std::filesystem;
using namespace std;

MONOCHROME_CAPI BOOL MONOCHROME_INITIALIZER_NAME(const char* appBaseDirectory) {
    fs::path appBasePath(appBaseDirectory);
    
    fs::path monochromeDirPath(appBasePath);
    monochromeDirPath /= "monochrome";
    
    fs::path monoDirPath(appBasePath);
    monoDirPath /= "mono";
    
    fs::path monoAssemblyDirPath(monoDirPath);
    monoAssemblyDirPath /= "lib";
    
    fs::path monoConfigDirPath(monoDirPath);
    monoConfigDirPath /= "etc";
    
    cout << "MonoChrome says hello, C++ world. Here are init paths:" << endl
         << "  Application base path: " << appBasePath.string() << endl
         << "  Mono binaries path: " << monoAssemblyDirPath.string() << endl
         << "  Mono config path: " << monoConfigDirPath.string() << endl
         << "  Mono runtime build information: " << mono_get_runtime_build_info() << endl;
    
    create_directories(monoAssemblyDirPath);
    create_directories(monoConfigDirPath);
    create_directories(monochromeDirPath);
    
    mono_set_dirs(
        monoAssemblyDirPath.string().c_str(),
        monoConfigDirPath.string().c_str()
    );
    
    fs::path monochromeAssemblyPath(monochromeDirPath);
    monochromeAssemblyPath /= "MonoChrome.dll";
        
    cout << "Creating MonoChrome app domain." << endl;
    MonoDomain* domain = mono_jit_init("MonoChrome");
    
    cout << "Now loading " << monochromeAssemblyPath.string() << endl;
    MonoAssembly* assembly = mono_domain_assembly_open(domain, monochromeAssemblyPath.string().c_str());
    if (assembly) {
        cout << "Assembly loaded, retrieving image." << endl;
        MonoImage* image = mono_assembly_get_image(assembly);
        
        if (image) {    
            MonoImageOpenStatus status;
            mono_assembly_load_references(image, &status); 
            
            cout << "Image retrieved, looking for the initializer..." << endl;
            MonoMethodDesc* desc = mono_method_desc_new("MonoChrome.Core:Initialize(string)", true);
            MonoMethod* method = mono_method_desc_search_in_image(desc, image);
            
            if (method) {
                void* argv[1] = { nullptr };
                argv[0] = mono_string_new(domain, "FEEL THE POWER OF GOD!");
                
                cout << "Method found, invoking..." << endl;
                mono_runtime_invoke(method, nullptr, argv, nullptr);
            }
        }
    }
    
    return TRUE;
}