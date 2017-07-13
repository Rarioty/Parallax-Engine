#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include <Parallax/fs/IFileSystem.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::fs
     * \ingroup     PIL
     */
    namespace fs
    {
        /**
         * \class   FileHandler
         * \brief   Class to handle files on specific operating system
         *
         * \ingroup PIL
         */
        class FileHandler
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            FileHandler(){}
            /**
             * \brief
             *  Destructor
             */
            ~FileHandler(){}

            /**
             * \brief
             *  Clone this file handler
             *
             * \return  Copy of this file handler
             */
            virtual std::unique_ptr<FileHandler>        clone() const = 0;

            /**
             * \brief
             *  Get the associated file system
             *
             * \return  Associated file system
             */
            virtual IFileSystem*                        fs() const = 0;
            /**
             * \brief
             *  Update file infos
             */
            virtual void                                updateFileInfo() = 0;

            /**
             * \brief
             *  Get the path of the file
             *
             * \return  Path of the file
             */
            virtual std::string                         path() const = 0;

            /**
             * \brief
             *  Is the file exists physically ?
             *
             * \return  True if the file exists, false otherwise
             */
            virtual bool                                exists() = 0;
            /**
             * \brief
             *  Is this file a physical file ?
             *
             * \return  True if this is a physical file, false otherwise
             */
            virtual bool                                isFile() = 0;
            /**
             * \brief
             *  Is this file a directory ?
             *
             * \return  True if this file is a directory, false otherwise
             */
            virtual bool                                isDirectory() = 0;
            /**
             * \brief
             *  Is this file a symbolic link ?
             *
             * \return  True if this file is a symbolic link, false otherwise
             */
            virtual bool                                isSymbolicLink() = 0;
            /**
             * \brief
             *  Get the content of a directory
             *
             * \return  Vector of paths to all files in this directory
             */
            virtual Collections::Vector<std::string>    listFiles() const = 0;

            /**
             * \brief
             *  Get the size of this file
             *
             * \return  Filesize
             */
            virtual U32                                 size() = 0;
            /**
             * \brief
             *  Get last access time of this file
             *
             * \return  Last access time
             */
            virtual U32                                 lastAccessTime() = 0;
            /**
             * \brief
             *  Get last modification time of this file
             *
             * \return  Last modification time
             */
            virtual U32                                 lastModificationTime() = 0;

            /**
             * \brief
             *  Create a directory with this file path
             *
             * \return  True if the directory has been created, false otherwise
             */
            virtual bool                                createDirectory() = 0;
            /**
             * \brief
             *  Remove a directory with this file path
             *
             * \return  True if the directory has been removed, false otherwise
             */
            virtual bool                                removeDirectory() = 0;

            /**
             * \brief
             *  Copy the file elsewhere
             *
             * \param[in]   dest    Destination for the copy
             *
             * \return  True if the file has been copied, false otherwise
             */
            virtual bool                                copy(FileHandler& dest) = 0;
            /**
             * \brief
             *  Move the file elsewhere
             *
             * \param[in]   dest    Destination for the file
             *
             * \return  True if the file has been moved, false otherwise
             */
            virtual bool                                move(FileHandler& dest) = 0;

            /**
             * \brief
             *  Create a hard link for this file
             *
             * \param[in]   dest    Path of the hard link
             *
             * \return  True if the hard link has been created, false otherwise
             */
            virtual bool                                createLink(FileHandler& dest) = 0;
            /**
             * \brief
             *  Create a symbolic link for this file
             *
             * \param[in]   dest    Path of the symbolic link
             *
             * \return  True if the symbolic link has been created, false otherwise
             */
            virtual bool                                createSymbolicLink(FileHandler& dest) = 0;

            /**
             * \brief
             *  Rename this file
             *
             * \param[in]   filename    New file name
             *
             * \return  True if the file has been renamed, false otherwise
             */
            virtual bool                                rename(const std::string& filename) = 0;
            /**
             * \brief
             *  Remove this file
             *
             * \return  True if this file has been removed, false otherwise
             */
            virtual bool                                remove() = 0;

            /**
             * \brief
             *  Get an input stream of this file
             *
             * \param[in]   mode    Mode for opening the file
             *
             * \return  Input stream of this file
             */
            virtual std::unique_ptr<std::istream>       createInputStream(std::ios_base::openmode mode) const = 0;
            /**
             * \brief
             *  Get an output stream of this file
             *
             * \param[in]   mode    Mode for opening the file
             *
             * \return  Output stream of this file
             */
            virtual std::unique_ptr<std::ostream>       createOutputStream(std::ios_base::openmode mode) = 0;
        };
    }
}

#endif
