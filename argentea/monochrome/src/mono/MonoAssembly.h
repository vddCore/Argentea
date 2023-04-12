#ifndef ARGENTEA_MONOASSEMBLY_H
#define ARGENTEA_MONOASSEMBLY_H

#include <exception>
#include <string>
#include <memory>

#include "mono/metadata/assembly.h"

namespace MonoChrome::Mono {
    class Class;
    
    class Assembly {
    private:
        MonoAssembly* _unsafeAssembly;
        MonoImage* _assemblyImage;
        MonoAssemblyName* _assemblyName;

    public:
        explicit Assembly(MonoAssembly* unsafeAssembly);
        ~Assembly();
        
        std::shared_ptr<Mono::Class> FindClass(std::string nameSpace, std::string className);
        
        MonoImage* getUnsafeImage();
        std::string getFullName();
    };
} // Mono

#endif //ARGENTEA_MONOASSEMBLY_H
