#ifndef CSVROW_HPP
#define CSVROW_HPP

#include <PIL/Collections/Vector.hpp>
#include <PIL/Types.hpp>
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
                CSVRow(Collections::Vector<std::string>& headers);
                ~CSVRow();

            public:
                U32                     size() const;
                void                    push(const std::string& value);
                bool                    set(const std::string& key, const std::string& value);

                template <typename T>
                const T                 get_value(U32 pos) const;

                const std::string       operator[](unsigned int) const;
                const std::string       operator[](std::string& value_name) const;
                friend std::ostream&    operator<<(std::ostream& os, const CSVRow& row);
                friend std::ofstream&   operator<<(std::ofstream& fs, const CSVRow& row);

            private:
                const Collections::Vector<std::string>  m_headers;
                const Collections::Vector<std::string>  m_values;
            };
        }
    }
}

#endif
