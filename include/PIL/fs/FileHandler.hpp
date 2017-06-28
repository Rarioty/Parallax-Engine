#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <PIL/fs/AbstractFileSystem.hpp>

namespace Parallax
{
    namespace fs
    {
        class FileHandler
        {
        public:
            FileHandler(){}
            ~FileHandler(){}

            virtual std::unique_ptr<FileHandler>        clone() const = 0;

            virtual AbstractFileSystem*                 fs() const = 0;
            virtual void                                updateFileInfo() = 0;

            virtual std::string                         path() const = 0;

            virtual bool                                exists() = 0;
            virtual bool                                isFile() = 0;
            virtual bool                                isDirectory() = 0;
            virtual bool                                isSymbolicLink() = 0;

            virtual Collections::Vector<std::string>    listFiles() const = 0;

            virtual U32                                 size() = 0;
            virtual U32                                 lastAccessTime() = 0;
            virtual U32                                 lastModificationTime() = 0;

            virtual bool                                createDirectory() = 0;
            virtual bool                                removeDirectory() = 0;

            virtual bool                                copy(FileHandler& dest) = 0;
            virtual bool                                move(FileHandler& dest) = 0;

            virtual bool                                createLink(FileHandler& dest) = 0;
            virtual bool                                createSymbolicLink(FileHandler& dest) = 0;

            virtual bool                                rename(const std::string& filename) = 0;
            virtual bool                                remove() = 0;

            virtual std::unique_ptr<std::istream>       createInputStream(std::ios_base::openmode mode) const = 0;
            virtual std::unique_ptr<std::ostream>       createOutputStream(std::ios_base::openmode mode) = 0;
        };
    }
}

#endif
