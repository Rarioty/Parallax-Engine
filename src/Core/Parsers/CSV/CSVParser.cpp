#include <Parallax/Parsers/CSV/CSVParser.hpp>

#include <fstream>
#include <sstream>
#include <iomanip>

namespace Parallax::Core::Parser
{
    CSVParser::CSVParser(const std::string& filename, char sep)
        : m_filename(filename)
        , m_sep(sep)
    {
        std::string line;

        std::ifstream ifile(m_filename.c_str());
        if (ifile.is_open())
        {
            while (ifile.good())
            {
                getline(ifile, line);
                if (line != "")
                    m_original_file.push_back(line);
            }
            ifile.close();

            if (m_original_file.size() == 0)
                throw std::runtime_error("No data in file");

            parseHeaders();
            parseContent();
        }
        else
            throw std::runtime_error("Can't open file");
    }

    CSVParser::~CSVParser()
    {
        Collections::Vector<CSVRow*>::Iterator it;

        for (it = m_content.begin(); it != m_content.end(); ++it)
            delete *it;
    }

    void CSVParser::parseHeaders(void)
    {
        std::stringstream ss(m_original_file.at(0));
        std::string item;

        while (std::getline(ss, item, m_sep))
            m_headers.push_back(item);
    }

    void CSVParser::parseContent(void)
    {
        Collections::Vector<std::string>::Iterator it;

        it = m_original_file.begin();
        ++it;

        for (; it != m_original_file.end(); ++it)
        {
            bool quoted = false;
            int tokenStart = 0;
            U32 i = 0;

            CSVRow* row = new CSVRow(m_headers);

            for (; i != it->length(); ++i)
            {
                if (it->at(i) == '"')
                    quoted = ((quoted) ? (false) : (true));
                else if (it->at(i) == ',' && !quoted)
                {
                    row->push(it->substr(tokenStart, i - tokenStart));
                    tokenStart = i+1;
                }
            }

            // End
            row->push(it->substr(tokenStart, it->length() - tokenStart));

            // If value(s) missing
            if (row->size() != m_headers.size())
                throw std::runtime_error("Corrupted data");
            m_content.push_back(row);
        }
    }

    CSVRow& CSVParser::getRow(U32 position)
    {
        if (position < m_content.size())
            return *(m_content.at(position));

        throw std::runtime_error("Can't return this row (too far");
    }

    CSVRow& CSVParser::operator[](U32 position)
    {
        return CSVParser::getRow(position);
    }

    U32 CSVParser::rowCount(void)
    {
        return m_content.size();
    }

    U32 CSVParser::columnCount(void)
    {
        return m_headers.size();
    }

    Collections::Vector<std::string> CSVParser::getHeaders(void) const
    {
        return m_headers;
    }

    const std::string CSVParser::getHeaderElement(U32 pos)
    {
        if (pos >= m_headers.size())
            throw std::runtime_error("Header wanted is too far");

        return m_headers.at(pos);
    }

    bool CSVParser::deleteRow(U32 pos)
    {
        if (pos < m_content.size())
        {
            delete m_content.at(pos);
            m_content.remove(pos);
            return true;
        }

        return false;
    }

    bool CSVParser::addRow(U32 pos, Collections::Vector<std::string>& s)
    {
        CSVRow* row = new CSVRow(m_headers);

        for (auto it = s.begin(); it != s.end(); ++it)
            row->push(*it);

        if (pos <= m_content.size())
        {
            m_content.insert(row, pos);
            return true;
        }

        delete row;
        return false;
    }

    void CSVParser::sync(void)
    {
        std::ofstream f;
        f.open(m_filename, std::ios::out | std::ios::trunc);

        // Headers
        U32 i = 0;
        for (auto it = m_headers.begin(); it != m_headers.end(); ++it)
        {
            f << *it;
            if (i < m_headers.size() - 1)
                f << ',';
            else
                f << std::endl;

            i++;
        }

        for (auto it = m_content.begin(); it != m_content.end(); ++it)
        {
            f << **it << std::endl;
        }

        f.close();
    }

    const std::string& CSVParser::getFilename(void) const
    {
        return m_filename;
    }
}
