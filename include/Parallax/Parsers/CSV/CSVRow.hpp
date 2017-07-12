#ifndef CSVROW_HPP
#define CSVROW_HPP

#include <Parallax/Collections/Vector.hpp>
#include <Parallax/Types.hpp>
#include <sstream>
#include <string>

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
             * \class   CSVRow
             * \brief   Row from a CSV file format
             *
             * \ingroup Core
             */
            class CSVRow
            {
            public:
                /**
                 * \brief
                 *  Constructor
                 *
                 * \param[in]   headers     Headers for the values in this row
                 */
                CSVRow(Collections::Vector<std::string>& headers);
                /**
                 * \brief
                 *  Destructor
                 */
                ~CSVRow();

            public:
                /**
                 * \brief
                 *  Get the size of this row
                 *
                 * \return  Size of this row
                 */
                U32                     size();
                /**
                 * \brief
                 *  Push an element into this row
                 *
                 * \param[in]   value   Value to push
                 */
                void                    push(const std::string& value);
                /**
                 * \brief
                 *  Change the value
                 *
                 * \param[in]   key     Key of the value to change
                 * \param[in]   value   New value
                 *
                 * \return  Whether or not we succeeded to change the value
                 */
                bool                    set(const std::string& key, const std::string& value);

                /**
                 * \brief
                 *  Get a value
                 *
                 * \tparam  T   Output type of the value
                 *
                 * \param[in]   pos     Position of the value to get
                 *
                 * \return  The value typped
                 */
                template <typename T>
                const T                 getValue(U32 pos);

                /**
                 * \brief
                 *  Get a value
                 *
                 * \param[in]   position    Position of the value to get
                 *
                 * \return  The wanted value
                 */
                const std::string       operator[](U32 position);
                /**
                 * \brief
                 *  Get a value
                 *
                 * \param[in]   key     The key of the value
                 *
                 * \return  The wanted value
                 */
                const std::string       operator[](std::string& key);
                /**
                 * \brief
                 *  Write this row in a stream
                 *
                 * \param[in]   os  Strema to write into
                 * \param[in]   row Row to write into the stream
                 *
                 * \return  The stream after writting
                 */
                friend std::ostream&    operator<<(std::ostream& os, CSVRow& row);
                /**
                 * \brief
                 *  Write this row in a file stream
                 *
                 * \param[in]   os  File stream to write into
                 * \param[in]   row Row to write into the stream
                 *
                 * \return  The file stream after writting
                 */
                friend std::ofstream&   operator<<(std::ofstream& os, CSVRow& row);

            private:
                Collections::Vector<std::string>  m_headers;    /*!<    Headers of the values   */
                Collections::Vector<std::string>  m_values;     /*!<    Values in this row      */
            };

            #include "CSVRow.inc"
        }
    }
}

#endif
