#include "Mono.h"

#include "MonoDomain.h"

namespace MonoChrome::Mono {
    std::shared_ptr<Mono::Domain> Initialize(fs::path& basePath, const std::string& domainName) {
        if (_initialized) {
            throw std::exception("Mono subsystem has already been initialized.");
        }

        if (_destroyed) {
            throw std::exception("This Mono subsystem has been destroyed and cannot be re-initialized.");
        }

        _libPath = fs::path(basePath) / "mono/lib";
        _etcPath = fs::path(basePath) / "mono/etc";

        if (!fs::is_directory(_libPath)) {
            throw std::exception(
                _libPath.string()
                    .append(" was not found.")
                    .c_str()
            );
        }

        if (!fs::is_directory(_etcPath)) {
            throw std::exception(
                _etcPath.string()
                    .append(" was not found.")
                    .c_str()
            );
        }

        mono_set_dirs(
            _libPath.string().c_str(),
            _etcPath.string().c_str()
        );

        MonoDomain* domain = mono_jit_init(domainName.c_str());

        if (!domain) {
            throw std::exception(
                std::string("Failed to initialize Mono JIT for domain '")
                    .append(domainName)
                    .append("'")
                    .c_str()
            );
        }

        _initialized = true;
        return std::make_shared<Mono::Domain>(domain);
    }

    void ShutDown(const std::shared_ptr<Mono::Domain>& domain) {
        if (!_initialized) {
            throw std::exception("Mono subsystem has not been initialized yet.");
        }

        mono_jit_cleanup(domain->getUnsafeDomain());

        _initialized = false;
        _destroyed = true;
    }
}
