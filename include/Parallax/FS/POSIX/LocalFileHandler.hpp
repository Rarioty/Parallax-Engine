#ifndef PARALLAX_LOCAL_FILE_HANDLER_HPP_GUARD
#define PARALLAX_LOCAL_FILE_HANDLER_HPP_GUARD

#include <Parallax/FS/POSIX/LocalFileSystem.hpp>
#include <Parallax/FS/FileHandler.hpp>

namespace Parallax
{
    namespace FS
    {
        class LocalFileHandler : public FileHandler
        {
        public:
            LocalFileHandler(std::shared_ptr<LocalFileSystem> fs, const std::string& path);
            ~LocalFileHandler();

            std::unique_ptr<FileHandler>        clone() const;

            IFileSystem*                        fs() const;
            void                                updateFileInfo();

            std::string                         path() const;

            bool                                exists();
            bool                                isFile();
            bool                                isDirectory();
            bool                                isSymbolicLink();

            Collections::Vector<std::string>    listFiles() const;

            U32                                 size();
            U32                                 lastAccessTime();
            U32                                 lastModificationTime();

            bool                                createDirectory();
            bool                                removeDirectory();

            bool                                copy(FileHandler& dest);
            bool                                move(FileHandler& dest);

            bool                                createLink(FileHandler& dest);
            bool                                createSymbolicLink(FileHandler& dest);

            bool                                rename(const std::string& filename);
            bool                                remove();

            std::unique_ptr<std::istream>       createInputStream(std::ios_base::openmode mode) const;
            std::unique_ptr<std::ostream>       createOutputStream(std::ios_base::openmode mode);

        private:
            void readFileInfo();
            void readLinkInfo();

        private:
            std::shared_ptr<LocalFileSystem>    m_fs;
            std::string                         m_path;
            void*                               m_fileInfo;
            void*                               m_linkInfo;
        };
    }
}

#endif
