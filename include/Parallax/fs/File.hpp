#ifndef FILE_HPP
#define FILE_HPP

#include <Parallax/Collections/Vector.hpp>
#include <Parallax/Types.hpp>

#include <iostream>
#include <sstream>
#include <memory>

namespace Parallax
{
    namespace fs
    {
        class FileHandler;

        class File
        {
        public:
            File();
            File(const File& file);
            File(std::unique_ptr<FileHandler>&& handler);
            ~File();

            File&                               operator=(const File& file);

            std::string                         path() const;
            std::string                         filename() const;

            void                                updateFileInfo();

            bool                                exists() const;
            bool                                isFile() const;
            bool                                isDirectory() const;
            bool                                isSymbolicLink() const;

            Collections::Vector<std::string>    listFiles() const;

            U32                                 size() const;
            U32                                 lastAccessTime() const;
            U32                                 lastModificationTime() const;

            std::string                         sha1() const;

            File                                parentDirectory();
            File                                open(const std::string& path);

            bool                                createDirectory();
            bool                                removeDirectory();

            void                                copyDirectoryRec(File& dstDir);
            void                                removeDirectoryRec();

            bool                                copy(File& dest);
            bool                                move(File& dest);

            bool                                createLink(File& dest);
            bool                                createSymbolicLink(File& dest);

            bool                                rename(const std::string& filename);
            bool                                remove();

            std::unique_ptr<std::istream>       createInputStream(std::ios_base::openmode mode = std::ios_base::in) const;
            std::unique_ptr<std::ostream>       createOutputStream(std::ios_base::openmode mode = std::ios_base::out);

            std::string                         readFile() const;
            bool                                writeFile(const std::string& content);

        protected:
            bool                                genericCopy(File& dst);
            bool                                genericMove(File& dst);

        protected:
            std::unique_ptr<FileHandler>    m_handler;
        };
    }
}

#endif
