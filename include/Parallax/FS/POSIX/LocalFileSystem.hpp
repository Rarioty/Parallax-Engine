#ifndef PARALLAX_LOCAL_FILE_SYSTEM_HPP_GUARD
#define PARALLAX_LOCAL_FILE_SYSTEM_HPP_GUARD

#include <Parallax/FS/IFileSystem.hpp>
#include <Parallax/FS/File.hpp>

#include <memory>

namespace Parallax
{
    namespace FS
    {
        class LocalFileSystem : public IFileSystem, public std::enable_shared_from_this<LocalFileSystem>
        {
        public:
            LocalFileSystem();
            ~LocalFileSystem() override;

            File open(const std::string& path) override;
        };
    }
}

#endif
