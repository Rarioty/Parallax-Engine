#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <PIL/Types.hpp>

#include <string>
#include <fstream>

namespace Parallax
{
    /**
     * \class   File
     * \brief   This class handle a file in the engine
     */
    class File
    {
    public:
        /**
         * \enum    openmode
         * \brief   Differents modes to open a file
         */
        enum openmode
        {
            IN,         /*!<    Open file for read purposes                     */
            OUT,        /*!<    Open file for write purposes                    */
            BINARY,     /*!<    Open file in binary mode                        */
            ATE,        /*!<    Open file and place the cursor at the end       */
            APP,        /*!<    Open file and append content                    */
            TRUNC       /*!<    Open file and erase previous content            */
        };

    public:
        /**
         * \brief   Constructor
         *
         * \param[in]   filepath    Path to the target file
         * \param[in]   mode        Modes to use to open the file
         */
        File(std::string filepath, openmode mode);

        /**
         * \brief   Open this file
         *
         * \return  An error code or 0 if it succeeded
         */
        int open();
        /**
         * \brief   Close this file
         *
         * \return  An error code or 0 if it succeeded
         */
        int close();

        /**
         * \brief   Get the filepath to the physical file
         *
         * \return  Path to the file
         */
        std::string getFilepath() const;
        /**
         * \brief   Get the modes used to open this file
         *
         * \return  Modes used
         */
        openmode getOpenmode() const;

    private:
        std::string     m_filepath;     /*!<    Path to the file                            */
        openmode        m_openmode;     /*!<    Modes used to open the file                 */
        std::fstream*   m_stream;       /*!<    Stream used to read/write into the file     */
    };
}

#endif
