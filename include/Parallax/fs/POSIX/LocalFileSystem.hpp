#ifndef LOCAL_FILE_SYSTEM_HPP
#define LOCAL_FILE_SYSTEM_HPP

#include <Parallax/fs/AbstractFileSystem.hpp>
#include <Parallax/fs/File.hpp>

#include <memory>

namespace Parallax
{
    namespace fs
    {
        class LocalFileSystem : public AbstractFileSystem, public std::enable_shared_from_this<LocalFileSystem>
        {
        public:
            LocalFileSystem();
            ~LocalFileSystem();

            File open(const std::string& path) override;
        };
    }
}

#endif
