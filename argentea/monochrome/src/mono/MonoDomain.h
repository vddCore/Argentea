#ifndef ARGENTEA_MONODOMAIN_H
#define ARGENTEA_MONODOMAIN_H

#include <filesystem>
#include <exception>
#include <memory>
#include <set>

#include <mono/metadata/appdomain.h>

namespace fs = std::filesystem;

namespace MonoChrome::Mono {
    class Assembly;

    class Domain {
    private:
        MonoDomain* _unsafeDomain;
        std::set<std::shared_ptr<Mono::Assembly>> _loadedAssemblies;

    public:
        explicit Domain(MonoDomain* unsafeDomain);

        std::shared_ptr<Mono::Assembly> LoadAssembly(fs::path& assemblyPath);
        void UnloadAssembly(const std::shared_ptr<Mono::Assembly>& assembly);
        
        MonoDomain* getUnsafeDomain() { return _unsafeDomain; }
        std::string getName() { return mono_domain_get_friendly_name(_unsafeDomain); }
    };
} // Mono

#endif //ARGENTEA_MONODOMAIN_H
