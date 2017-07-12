template <typename T>
Vector<T>::Vector(U32 start_size)
    : m_current(0)
    , m_max_size(start_size)
    , m_array(nullptr)
{
    if (start_size == 0)
        throw std::runtime_error("Vector cannot have a starting length of 0");

    m_array = new T[start_size];
}

template <typename T>
Vector<T>::Vector(const Vector& vec)
    : m_current(vec.m_current)
    , m_max_size(vec.m_max_size)
{
    U32 i;

    m_array = new T[vec.m_max_size];
    for (i = 0; i < vec.m_current; ++i)
    {
        m_array[i] = vec.m_array[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] m_array;
}

template <typename T>
T* Vector<T>::begin()
{
    return m_array;
}

template <typename T>
T* Vector<T>::end()
{
    return m_array+m_current;
}

template <typename T>
void Vector<T>::push_front(T element)
{
    U32 i;

    if (m_current + 1 == m_max_size)
        resize(2 * m_max_size);

    for (i = m_current; i > 0; --i)
    {
        m_array[i] = m_array[i-1];
    }

    m_array[0] = element;
    m_current++;
}

template <typename T>
void Vector<T>::push_back(T element)
{
    // Check size of the array
    if (m_current + 1 == m_max_size)
        resize(2 * m_max_size);

    m_array[m_current++] = element;
}

template <typename T>
void Vector<T>::insert(T element, U32 position)
{
    if (position > m_current)
    {
        while (m_max_size < position)
        {
            m_max_size *= 2;
        }
        resize(m_max_size);
    }

    m_array[position] = element;
    m_current = position + 1;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_current == 0)
        throw std::runtime_error("Can't pop an element on a zero size container");

    m_current--;
}

template <typename T>
U32 Vector<T>::size()
{
    return m_current;
}

template <typename T>
void Vector<T>::resize(U32 new_size)
{
    U32 i;

    if (new_size < m_max_size)
        throw std::runtime_error("Resize to a smaller size than before");

    if (new_size == m_max_size)
        return;

    T* new_array = new T[new_size];

    for (i = 0; i < m_current; ++i)
    {
        new_array[i] = m_array[i];
    }

    delete[] m_array;

    m_max_size = new_size;
    m_array = new_array;
}

template <typename T>
void Vector<T>::remove(U32 position)
{
    U32 i;

    if (position >= m_current)
        throw std::runtime_error("Try to erase element after max size");

    for (i = position; i < m_current; ++i)
    {
        m_array[i] = m_array[i+1];
    }
    m_current--;
}

template <typename T>
void Vector<T>::remove(const std::function<bool(U32, T)>& func)
{
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        if (func(i, m_array[i]))
        {
            remove(i--);
        }
    }
}

template <typename T>
T Vector<T>::get(U32 position)
{
    if (position >= m_current)
        throw std::runtime_error("Can't access values after max size !");

    return m_array[position];
}

template <typename T>
T Vector<T>::front()
{
    if (m_current == 0)
        throw std::runtime_error("Can't access a zero element vector");

    return m_array[0];
}

template <typename T>
T Vector<T>::back()
{
    if (m_current == 0)
        throw std::runtime_error("Can't access a zero element vector");

    return m_array[m_current-1];
}

template <typename T>
T& Vector<T>::at(U32 position)
{
    if (position >= m_current)
        throw std::runtime_error("Can't access values after max size !");

    return m_array[position];
}

template <typename T>
void Vector<T>::execute(const std::function<void(U32, T*)>& func)
{
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        func(i, &(m_array[i]));
    }
}

template <typename T>
void Vector<T>::execute(const std::function<bool(U32, T*)>& func)
{
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        if (!func(i, &(m_array[i])))
            break;
    }
}

template <typename T>
T Vector<T>::random()
{
    U32 pos;

    if (size() == 0)
        throw std::runtime_error("Size is 0 but a random element is asked");

    pos = rand() % m_current;

    return m_array[pos];
}

template <typename T>
std::pair<bool, U32> Vector<T>::find(T needle)
{
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        if (m_array[i] == needle)
            return std::make_pair(true, i);
    }

    return std::make_pair(false, 0);
}

template <typename T>
std::pair<bool, U32> Vector<T>::find_back(T needle)
{
    U32 i;

    for (i = m_current-1; i > 0; --i)
    {
        if (m_array[i] == needle)
            return std::make_pair(true, i);
    }

    if (m_current != 0 && m_array[0] == needle)
        return std::make_pair(true, 0);

    return std::make_pair(false, 0);
}

template <typename T>
std::pair<U32, U32*> Vector<T>::find_all(T needle)
{
    return find_all([needle](U32 position, T* element){
        return *element == needle;
    });
}

template <typename T>
std::pair<U32, U32*> Vector<T>::find_all(const std::function<bool(U32, T*)>& func)
{
    U32* results;
    U32 count;
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        if (func(i, &(m_array[i])))
            count++;
    }

    if (count == 0)
        return std::make_pair(0, nullptr);

    results = new U32[count];

    count = 0;
    for (i = 0; i < m_current; ++i)
    {
        if (func(i, &(m_array[i])))
            results[count++] = i;
    }

    return std::make_pair(count, results);
}

template <typename T>
void quicksort(T* array, U32 len, const std::function<bool(T, T)>& comparator)
{
    if (len < 2)
        return;

    T pivot = array[len / 2];

    U32 i, j;
    for (i = 0, j = len-1; ; i++, j--)
    {
        while (comparator(array[i], pivot) && array[i] != pivot)  i++;
        while (!comparator(array[j], pivot) && array[j] != pivot) j--;

        if (i >= j) break;

        T tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    quicksort(array, i, comparator);
    quicksort(array + i, len - i, comparator);
}

template <typename T>
void Vector<T>::sort(const std::function<bool(T, T)>& comparator)
{
    quicksort(m_array, m_current, comparator);
}
