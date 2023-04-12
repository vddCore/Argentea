#ifndef ARGENTEA_MONOCLASS_H
#define ARGENTEA_MONOCLASS_H

#include <algorithm>
#include <utility>
#include <string>
#include <exception>

#include <mono/jit/jit.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>

namespace MonoChrome::Mono {
    class Assembly;
    
    class Class {
    private:
        std::string _nameSpace;
        std::string _className;
        Mono::Assembly* _ownerAssembly = nullptr;
        MonoClass* _unsafeClass;

    public:
        explicit Class(Mono::Assembly* ownerAssembly, MonoClass* unsafeClass);
        Class(Mono::Assembly* ownerAssembly, std::string& nameSpace, std::string& className);
        
        Mono::Assembly* getOwnerAssembly();
        std::string getNameSpace();
        std::string getName();
    };
} // Mono

#endif //ARGENTEA_MONOCLASS_H
