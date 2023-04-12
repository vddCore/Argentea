#include "MonoAssembly.h"
#include "MonoClass.h"

#include <memory>

namespace MonoChrome::Mono {
    Assembly::Assembly(MonoAssembly* unsafeAssembly) {
        if (!_unsafeAssembly) {
            throw std::exception("A null pointer to an unsafe Mono assembly was passed.");
        }

        _unsafeAssembly = unsafeAssembly;
        _assemblyImage = mono_assembly_get_image(_unsafeAssembly);
        _assemblyName = mono_assembly_get_name(_unsafeAssembly);
    }

    Assembly::~Assembly() {
        if (_unsafeAssembly) {
            mono_assembly_close(_unsafeAssembly);
        }
    }

    std::shared_ptr<Mono::Class> Assembly::FindClass(std::string nameSpace, std::string className) {
        return std::make_shared<Mono::Class>(
            this,
            nameSpace,
            className
        );
    }

    MonoImage* Assembly::getUnsafeImage() {
        return _assemblyImage;
    }

    std::string Assembly::getFullName() {
        return {mono_assembly_name_get_name(_assemblyName)};
    }
}