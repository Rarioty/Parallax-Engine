#include <Core/Parsers/CSV/CSVRow.hpp>

namespace Parallax::Core::Parser
{
    CSVRow::CSVRow(Collections::Vector<std::string>& headers)
        : m_headers(headers)
    {

    }

    CSVRow::~CSVRow()
    {}

    U32 CSVRow::size()
    {
        return m_values.size();
    }

    void CSVRow::push(std::string& value)
    {
        m_values.push_back(value);
    }

    bool CSVRow::set(const std::string& key, const std::string& value)
    {
        Collections::Vector<std::string>::Iterator it;
        U32 pos = 0;

        for (it = m_headers.begin(); it != m_headers.end(); ++it)
        {
            if (key == *it)
            {
                m_values[pos] = value;
                return true;
            }
            pos++;
        }

        return false;
    }

    const std::string CSVRow::operator[](U32 position) const
    {
        if (position < m_values.size())
            return m_values[position];

        throw std::runtime_error("Value asked is too far");
    }

    const std::string CSVRow::operator[](const std::string& key) const
    {
        Collections::Vector<std::string>::Iterator it;
        int pos = 0;

        for (it = m_headers.begin(); it != m_headers.end(); ++it)
        {
            if (key == *it)
                return m_values[pos];

            pos++;
        }

        throw std::runtime_error("Value asked is too far");
    }

    std::ostream& operator<<(std::ostream& os, const CSVRow& row)
    {
        for (U32 i = 0; i != row.m_values.size(); ++i)
            os << row.m_values[i] << " | ";

        return os;
    }

    std::ofstream& operator<<(std::ofstream& os, const CSVRow& row)
    {
        for (U32 i = 0; i != row.m_values.size(); ++i)
        {
            os << row.m_values[i];
            if (i < row.m_values.size() - 1)
                os << ",";
        }

        return os;
    }
}
