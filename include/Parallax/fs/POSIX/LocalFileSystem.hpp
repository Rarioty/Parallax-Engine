#ifndef PARALLAX_LOCAL_FILE_SYSTEM_HPP_GUARD
#define PARALLAX_LOCAL_FILE_SYSTEM_HPP_GUARD

#include <Parallax/fs/IFileSystem.hpp>
#include <Parallax/fs/File.hpp>

#include <memory>

namespace Parallax
{
    namespace fs
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
