#include "MonoClass.h"
#include "MonoAssembly.h"

namespace MonoChrome::Mono {
    Class::Class(Mono::Assembly* ownerAssembly, MonoClass* unsafeClass) {
        if (!unsafeClass) {
            throw std::exception("Attempt to initialize a class from a null pointer.");
        }

        _ownerAssembly = ownerAssembly;
        _unsafeClass = unsafeClass;
        _nameSpace = mono_class_get_namespace(_unsafeClass);
        _className = mono_class_get_name(_unsafeClass);
    }

    Class::Class(Mono::Assembly* ownerAssembly, std::string& nameSpace, std::string& className) {
        _ownerAssembly = ownerAssembly;

        _nameSpace = nameSpace;
        _className = className;

        _unsafeClass = mono_class_from_name(
            _ownerAssembly->getUnsafeImage(),
            _nameSpace.c_str(),
            _className.c_str()
        );

        if (!_unsafeClass) {
            throw std::exception(
                std::string("Class ")
                    .append(_nameSpace)
                    .append(_className)
                    .append(" was not found in this assembly.")
                    .c_str()
            );
        }
    }
    
    Mono::Assembly* Class::getOwnerAssembly() {
        return _ownerAssembly;
    }
    
    std::string Class::getNameSpace() {
        return _nameSpace;
    }
    
    std::string Class::getName() {
        return _className;
    }
} // Mono