template <typename T>
const T CSVRow::getValue(U32 pos)
{
    if (pos < m_values.size())
    {
        T res;
        std::stringstream ss;
        ss << m_values.at(pos);
        ss >> res;

        return res;
    }

    throw std::runtime_error("Value wanted is too far");
}
