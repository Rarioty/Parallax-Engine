#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <Parallax/Parsers/CSV/CSVRow.hpp>
#include <Parallax/Collections/Vector.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::Core
     * \ingroup     Core
     */
    namespace Core
    {
        /**
         * \namespace   Parallax::Core::Parser
         * \ingroup     Core
         */
        namespace Parser
        {
            /**
             * \class   CSVParser
             * \brief   Parser for CSV file format
             *
             * \ingroup Core
             */
            class CSVParser
            {
            public:
                /**
                 * \brief
                 *  Constructor
                 *
                 * \param[in]   filename    File to parse name
                 * \param[in]   sep         Default separator of values
                 *
                 * \throw   std::runtime_error
                 */
                CSVParser(const std::string& filename, char sep = ',');
                /**
                 * \brief
                 *  Destructor
                 */
                ~CSVParser();

            public:
                /**
                 * \brief
                 *  Get a row of the csv file
                 *
                 * \param[in]   row     Number of the row to get
                 *
                 * \throw   std::runtime_error
                 *
                 * \return  The corresponding row
                 */
                CSVRow&                             getRow(U32 row);
                /**
                 * \brief
                 *  Get the number of row in the csv file
                 *
                 * \return  Number of row
                 */
                U32                                 rowCount();
                /**
                 * \brief
                 *  Get the number of columns in the csv file
                 *
                 * \return  Number of columns
                 */
                U32                                 columnCount();
                /**
                 * \brief
                 *  Get the headers of the csv file
                 *
                 * \return  Vector of headers strings
                 */
                Collections::Vector<std::string>    getHeaders(void) const;
                /**
                 * \brief
                 *  Get a specific header of the csv file
                 *
                 * \param[in]   pos     Number of the header
                 *
                 * \throw   std::runtime_error
                 *
                 * \return  Header specified
                 */
                const std::string                   getHeaderElement(U32 pos);
                /**
                 * \brief
                 *  Get the parsed file name
                 *
                 * \return  Filename
                 */
                const std::string&                  getFilename(void) const;

                /**
                 * \brief
                 *  Delete a row from the csv file
                 *
                 * \param[in]   row     Number of the row to delete
                 *
                 * \return  True if the row has been deleted, false otherwise
                 */
                bool                                deleteRow(U32 row);
                /**
                 * \brief
                 *  Add a row in the csv file
                 *
                 * \param[in]   pos     Position of the row in the csv file
                 * \param[in]   values  Strings values to insert
                 *
                 * \return  True if the operation succeeded, false otherwise
                 */
                bool                                addRow(U32 pos, Collections::Vector<std::string>& values);
                /**
                 * \brief
                 *  Synchronise the file
                 */
                void                                sync(void);

                /**
                 * \brief
                 *  Get a row of the csv file
                 *
                 * \param[in]   row     Number of the row to get
                 *
                 * \throw   std::runtime_error
                 *
                 * \return  The corresponding row
                 */
                CSVRow&                             operator[](U32 row);

            protected:
                /**
                 * \brief
                 *  Parse the headers of the csv file
                 */
                void                                parseHeaders(void);
                /**
                 * \brief
                 *  Parse the content of the csv file
                 */
                void                                parseContent(void);

            private:
                std::string                         m_filename;         /*!<    Parsed file name                */
                const char                          m_sep;              /*!<    Values separator                */

                Collections::Vector<std::string>    m_original_file;    /*!<    Lines of the original file      */
                Collections::Vector<std::string>    m_headers;          /*!<    List of headers of the csv file */
                Collections::Vector<CSVRow*>        m_content;          /*!<    List of values of the csv file  */
            };
        }
    }
}

#endif
