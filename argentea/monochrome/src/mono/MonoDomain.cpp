#include "MonoDomain.h"
#include "MonoAssembly.h"

namespace MonoChrome::Mono {
    Domain::Domain(MonoDomain* unsafeDomain)
        : _unsafeDomain(unsafeDomain) {

        if (!_unsafeDomain) {
            throw std::exception("Attempt to initialize a Mono::Domain with a null pointer.");
        }
    }

    std::shared_ptr<Mono::Assembly> Domain::LoadAssembly(fs::path& assemblyPath) {
        MonoAssembly* unsafeAssembly = mono_domain_assembly_open(
            _unsafeDomain,
            assemblyPath.string().c_str()
        );

        if (!unsafeAssembly) {
            throw std::exception(
                std::string("Failed to open assembly ")
                    .append(assemblyPath.string())
                    .c_str()
            );
        }

        auto assembly = std::make_shared<Mono::Assembly>(unsafeAssembly);
        _loadedAssemblies.insert(assembly);

        return assembly;
    }

    void Domain::UnloadAssembly(const std::shared_ptr<Mono::Assembly>& assembly) {
        if (std::find(_loadedAssemblies.begin(), _loadedAssemblies.end(), assembly) == _loadedAssemblies.end()) {
            throw std::exception("Attempt to unload an assembly loaded from outside of this Mono context.");
        }

        _loadedAssemblies.erase(assembly);
    }
} // Mono