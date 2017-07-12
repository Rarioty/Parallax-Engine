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
                CSVParser(const std::string& filename, char sep = ',');
                ~CSVParser();

            public:
                CSVRow&                             getRow(U32 row);
                U32                                 rowCount();
                U32                                 columnCount();
                Collections::Vector<std::string>    getHeaders(void) const;
                const std::string                   getHeaderElement(U32 pos);
                const std::string&                  getFilename(void) const;

                bool                                deleteRow(U32 row);
                bool                                addRow(U32 pos, Collections::Vector<std::string>& values);
                void                                sync(void);

                CSVRow&                             operator[](U32 row);

            protected:
                void                                parseHeaders(void);
                void                                parseContent(void);

            private:
                std::string                         m_filename;
                const char                          m_sep;

                Collections::Vector<std::string>    m_original_file;
                Collections::Vector<std::string>    m_headers;
                Collections::Vector<CSVRow*>        m_content;
            };
        }
    }
}

#endif
