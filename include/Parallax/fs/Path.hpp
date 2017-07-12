#ifndef PATH_HPP
#define PATH_HPP

#include <string>

namespace Parallax
{
    /**
     * \namespace   Parallax::fs
     * \ingroup     PIL
     */
    namespace fs
    {
        /**
         * \class   Path
         * \brief   Class to handle path
         *
         * \ingroup PIL
         */
        class Path
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            Path();
            /**
             * \brief
             *  Copy-Constructor
             *
             * \param[in]   path    Path to copy
             */
            Path(const Path& path);
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   path    Path to assign
             */
            Path(const std::string& path);
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   path    Path to assign
             */
            Path(const char* path);
            /**
             * \brief
             *  Destructor
             */
            ~Path();

            /**
             * \brief
             *  Copy another path
             *
             * \param[in]   path    Path to copy
             *
             * \return  New path
             */
            Path& operator=(const Path& path);

            /**
             * \brief
             *  Get the path
             *
             * \return  Path
             */
            const std::string& path() const;
            /**
             * \brief
             *  Set a new path
             *
             * \param[in]   path    New path
             */
            void setPath(const std::string& path);

            /**
             * \brief
             *  Get the path as native operating system form
             *
             * \return  Path
             */
            std::string toNative() const;

            /**
             * \brief
             *  Is the path empty ?
             *
             * \return  True if the path is empty, false otherwise
             */
            bool isEmpty() const;
            /**
             * \brief
             *  Does the path points to contents ?
             *
             * \return  True if the path points to contents, false otherwise
             */
            bool pointsToContents() const;
            /**
             * \brief
             *  Get the full path
             *
             * \return  Full path
             */
            const std::string& fullPath();

            /**
             * \brief
             *  Get the filename
             *
             * \return  filename
             */
            const std::string& filename();
            /**
             * \brief
             *  Get the basename
             *
             * \return  basename
             */
            const std::string& basename();
            /**
             * \brief
             *  Get the extension
             *
             * \return  extension
             */
            const std::string& extension();
            /**
             * \brief
             *  Get the directory path
             *
             * \return  directory path
             */
            const std::string& directoryPath();
            /**
             * \brief
             *  Get the drive letter
             *
             * \return  drive letter
             */
            const std::string& driveLetter();

            /**
             * \brief
             *  Is the path absolute
             *
             * \return True if the path is absolute, false otherwise
             */
            bool isAbsolute();
            /**
             * \brief
             *  Is the path relative
             *
             * \return True if the path is relative, false otherwise
             */
            bool isRelative();

            /**
             * \brief
             *  Append a new path to this one
             *
             * \param[in]   path    Path to append
             *
             * \return  Full path after the appending
             */
            Path resolve(Path path);
            /**
             * \brief
             *  Resolve all the '.' and '..' and return result
             *
             * \return  Resolved path
             */
            std::string resolved() const;

        private:
            /**
             * \brief
             *  Analyze the path
             */
            void analyze();

        private:
            std::string     m_path;                 /*!<    Original path                       */
            bool            m_pointsToContent;      /*!<    Does the path points to contents ?  */

            bool            m_details;              /*!<    Does the path has been analyzed ?   */
            std::string     m_fullPath;             /*!<    Full path of the path               */
            std::string     m_filename;             /*!<    Filename part of the path           */
            std::string     m_basename;             /*!<    Basename part of the path           */
            std::string     m_extension;            /*!<    Extension part of the path          */
            std::string     m_directoryPath;        /*!<    Directory part of the path          */
            std::string     m_driveLetter;          /*!<    Drive letter part of the path       */
            bool            m_absolute;             /*!<    Is the path absolute ?              */
        };
    }
}

#endif
