template <typename T>
Stack<T>::Stack(U32 starting_size)
    : m_max_size(starting_size)
    , m_current(0)
{
    if (starting_size == 0)
        throw std::runtime_error("The stack cannot have a zero element array");

    m_array = new T[starting_size];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_array;
}

template <typename T>
T& Stack<T>::top()
{
    if (m_current == 0)
        throw std::runtime_error("Cannot get top element on a zero element stack");

    return m_array[m_current-1];
}

template <typename T>
bool Stack<T>::empty()
{
    return m_current == 0;
}

template <typename T>
U32 Stack<T>::size()
{
    return m_current;
}

template <typename T>
void Stack<T>::push(T element)
{
    if (m_current + 1 == m_max_size)
        resize(m_max_size * 2);

    m_array[m_current++] = element;
}

template <typename T>
T Stack<T>::pop()
{
    if (m_current == 0)
        throw std::runtime_error("Cannot pop a zero element stack");
        
    return m_array[--m_current];
}

template <typename T>
void Stack<T>::resize(U32 new_size)
{
    T* new_array = new T[new_size];

    std::memcpy(new_array, m_array, m_current);
    delete m_array;

    m_array = new_array;
    m_max_size = new_size;
}
