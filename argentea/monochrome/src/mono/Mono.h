#ifndef ARGENTEA_MONO_H
#define ARGENTEA_MONO_H

#include <filesystem>
#include <memory>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/appdomain.h>

namespace fs = std::filesystem;

namespace MonoChrome::Mono {
    class Domain;

    namespace {
        bool _initialized;
        bool _destroyed;
        
        fs::path _libPath;
        fs::path _etcPath;
    }

    std::shared_ptr<Mono::Domain> Initialize(fs::path& basePath, const std::string& domainName);
    void ShutDown(const std::shared_ptr<Mono::Domain>& domain);
} // Mono

#endif //ARGENTEA_MONO_H
