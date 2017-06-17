template <typename T>
VectorIterator<T>::VectorIterator(Vector<T>* vector, U32 starting_position)
    : m_vector(vector)
    , m_current(starting_position)
{}

template <typename T>
VectorIterator<T>::~VectorIterator()
{}

template <typename T>
T VectorIterator<T>::operator*()
{
    if (m_current >= m_vector->size())
        throw std::runtime_error("Accessing iterator value but the target is incorrect");

    return m_vector->m_array[m_current];
}

template <typename T>
void VectorIterator<T>::next()
{
    m_current++;
}

template <typename T>
void VectorIterator<T>::operator++()
{
    return next();
}

template <typename T>
bool VectorIterator<T>::operator!=(VectorIterator<T> other)
{
    return m_current != other.m_current || m_vector != other.m_vector;
}

template <typename T>
bool VectorIterator<T>::operator==(VectorIterator<T> other)
{
    return m_current == other.m_current && m_vector == other.m_vector;
}

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
Vector<T>::~Vector()
{
    delete[] m_array;
}

template <typename T>
VectorIterator<T> Vector<T>::begin()
{
    return VectorIterator<T>(this, 0);
}

template <typename T>
VectorIterator<T> Vector<T>::end()
{
    return VectorIterator<T>(this, size());
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
U32 Vector<T>::size()
{
    return m_current;
}

template <typename T>
void Vector<T>::resize(U32 new_size)
{
    T* new_array = new T[new_size];

    std::memcpy(new_array, m_array, m_current);
    delete m_array;

    m_max_size = new_size;
    m_array = new_array;
}

template <typename T>
void Vector<T>::remove (U32 position)
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
void Vector<T>::remove(VectorIterator<T> it)
{
    remove (it.m_current);
    it.m_current--;
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

    for (i = m_current-1; i >= 0; --i)
    {
        if (m_array[i] == needle)
            return std::make_pair(true, i);
    }

    return std::make_pair(false, 0);
}

template <typename T>
std::pair<bool, U32*> Vector<T>::find_all(T needle)
{
    U32* results;
    U32 count;
    U32 i;

    for (i = 0; i < m_current; ++i)
    {
        if (m_array[i] == needle)
            count++;
    }

    if (count == 0)
        return std::make_pair(false, 0);

    results = new U32[count];

    count = 0;
    for (i = 0; i < m_current; ++i)
    {
        if (m_array[i] == needle)
            results[count++] = i;
    }

    return std::make_pair(true, results);
}

template <typename T>
std::pair<bool, U32*> Vector<T>::find_all(const std::function<bool(U32, T*)>& func)
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
        return std::make_pair(false, 0);

    results = new U32[count];

    count = 0;
    for (i = 0; i < m_current; ++i)
    {
        if (func(i, &(m_array[i])))
            results[count++] = i;
    }

    return std::make_pair(true, results);
}

template <typename T>
U32 partition(T* array, U32 start, U32 end)
{
    T x = array[start];
    T tmp;
    U32 i = start - 1;
    U32 j = end + 1;

    do {
        do {
            j--;
        } while (x > array[j]);

        do {
            i++;
        } while (x < array[i]);

        if (i < j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    } while(i < j);

    return j;
}

template <typename T>
void quicksort(T* array, U32 start, U32 end)
{
    U32 middle;

    if (start < end)
    {
        middle = partition(array, start, end);
        quicksort(array, start, middle);
        quicksort(array, middle+1, end);
    }
}

template <typename T>
void Vector<T>::sort(const std::function<bool(T, T)>& comparator)
{
    quicksort(m_array, 0, m_current);
}
