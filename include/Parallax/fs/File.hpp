#ifndef FILE_HPP
#define FILE_HPP

#include <Parallax/Collections/Vector.hpp>
#include <Parallax/Types.hpp>

#include <iostream>
#include <sstream>
#include <memory>

namespace Parallax
{
    /**
     * \namespace   Parallax::fs
     * \ingroup     PIL
     */
    namespace fs
    {
        class FileHandler;

        /**
         * \class   File
         * \brief   Class to handle files
         *
         * \ingroup PIL
         */
        class File
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            File();
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   file    Other file to copy
             */
            File(const File& file);
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   handler Handler to use with this file
             */
            File(std::unique_ptr<FileHandler>&& handler);
            /**
             * \brief
             *  Destructor
             */
            ~File();

            /**
             * \brief
             *  Copy other file
             *
             * \param[in]   file
             *
             * \return  New file after copy
             */
            File&                               operator=(const File& file);

            /**
             * \brief
             *  Get the path of the file
             *
             * \return  Path of the file
             */
            std::string                         path() const;
            /**
             * \brief
             *  Get the filename of the file
             *
             * \return  Filename
             */
            std::string                         filename() const;

            /**
             * \brief
             *  Update file infos
             */
            void                                updateFileInfo();

            /**
             * \brief
             *  Is the file exists physically ?
             *
             * \return  True if the file exists, false otherwise
             */
            bool                                exists() const;
            /**
             * \brief
             *  Is this file a physical file ?
             *
             * \return  True if this is a physical file, false otherwise
             */
            bool                                isFile() const;
            /**
             * \brief
             *  Is this file a directory ?
             *
             * \return  True if this file is a directory, false otherwise
             */
            bool                                isDirectory() const;
            /**
             * \brief
             *  Is this file a symbolic link ?
             *
             * \return  True if this file is a symbolic link, false otherwise
             */
            bool                                isSymbolicLink() const;

            /**
             * \brief
             *  Get the content of a directory
             *
             * \return  Vector of paths to all files in this directory
             */
            Collections::Vector<std::string>    listFiles() const;

            /**
             * \brief
             *  Get the size of this file
             *
             * \return  Filesize
             */
            U32                                 size() const;
            /**
             * \brief
             *  Get last access time of this file
             *
             * \return  Last access time
             */
            U32                                 lastAccessTime() const;
            /**
             * \brief
             *  Get last modification time of this file
             *
             * \return  Last modification time
             */
            U32                                 lastModificationTime() const;

            /**
             * \brief
             *  Get the SHA1 hash of this file
             *
             * \return  SHA1 hash
             */
            std::string                         sha1() const;

            /**
             * \brief
             *  Get the parent directory
             *
             * \return  File of the parent directory
             */
            File                                parentDirectory();
            /**
             * \brief
             *  Open a file in this directory
             *
             * \return  File opened
             */
            File                                open(const std::string& path);

            /**
             * \brief
             *  Create a directory with this file path
             *
             * \return  True if the directory has been created, false otherwise
             */
            bool                                createDirectory();
            /**
             * \brief
             *  Remove a directory with this file path
             *
             * \return  True if the directory has been removed, false otherwise
             */
            bool                                removeDirectory();

            /**
             * \brief
             *  Copy the directory recursively
             */
            void                                copyDirectoryRec(File& dstDir);
            /**
             * \brief
             *  Remove the directory recursively
             */
            void                                removeDirectoryRec();

            /**
             * \brief
             *  Copy the file elsewhere
             *
             * \param[in]   dest    Destination for the copy
             *
             * \return  True if the file has been copied, false otherwise
             */
            bool                                copy(File& dest);
            /**
             * \brief
             *  Move the file elsewhere
             *
             * \param[in]   dest    Destination for the file
             *
             * \return  True if the file has been moved, false otherwise
             */
            bool                                move(File& dest);

            /**
             * \brief
             *  Create a hard link for this file
             *
             * \param[in]   dest    Path of the hard link
             *
             * \return  True if the hard link has been created, false otherwise
             */
            bool                                createLink(File& dest);
            /**
             * \brief
             *  Create a symbolic link for this file
             *
             * \param[in]   dest    Path of the symbolic link
             *
             * \return  True if the symbolic link has been created, false otherwise
             */
            bool                                createSymbolicLink(File& dest);

            /**
             * \brief
             *  Rename this file
             *
             * \param[in]   filename    New file name
             *
             * \return  True if the file has been renamed, false otherwise
             */
            bool                                rename(const std::string& filename);
            /**
             * \brief
             *  Remove this file
             *
             * \return  True if this file has been removed, false otherwise
             */
            bool                                remove();

            /**
             * \brief
             *  Get an input stream of this file
             *
             * \param[in]   mode    Mode for opening the file
             *
             * \return  Input stream of this file
             */
            std::unique_ptr<std::istream>       createInputStream(std::ios_base::openmode mode = std::ios_base::in) const;
            /**
             * \brief
             *  Get an output stream of this file
             *
             * \param[in]   mode    Mode for opening the file
             *
             * \return  Output stream of this file
             */
            std::unique_ptr<std::ostream>       createOutputStream(std::ios_base::openmode mode = std::ios_base::out);

            /**
             * \brief
             *  Get the content of the file
             *
             * \return  String of the content of the file
             */
            std::string                         readFile() const;
            /**
             * \brief
             *  Write into the file
             *
             * \param[in]   content String to write into the file
             *
             * \return  True if the string has been writed, false otherwise
             */
            bool                                writeFile(const std::string& content);

        protected:
            bool                                genericCopy(File& dst);
            bool                                genericMove(File& dst);

        protected:
            std::unique_ptr<FileHandler>    m_handler;      /*!<    Handler for this file   */
        };
    }
}

#endif
