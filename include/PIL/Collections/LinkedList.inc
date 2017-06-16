template <typename T>
LinkedListIterator<T>::LinkedListIterator()
{
}

template <typename T>
LinkedListIterator<T>::~LinkedListIterator()
{
}

template <typename T>
T LinkedListIterator<T>::operator*()
{
}

template <typename T>
LinkedListIterator<T>& LinkedListIterator<T>::next()
{
}

template <typename T>
LinkedList<T>::LinkedList()
{
    m_front = m_back = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    struct node* current = m_front;

    while (current != m_back)
    {
        struct node* tmp = current->m_next;
        delete current;
        current = tmp;
    }
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::begin()
{

}

template <typename T>
LinkedListIterator<T> LinkedList<T>::end()
{

}

template <typename T>
void LinkedList<T>::push_front(T element)
{
    struct node* new_node = new struct node(element, m_front);

    if (m_front == nullptr)
        m_back = new_node;

    m_front = new_node;
}

template <typename T>
void LinkedList<T>::push_back(T element)
{
    struct node* new_node = new struct node(element, nullptr);

    if (m_front == nullptr)
    {
        m_front = m_back = new_node;
    }
    else
    {
        m_back = m_back->m_next = new_node;
    }
}

template <typename T>
void LinkedList<T>::insert(T element, U32 position)
{
    struct node* before = nullptr;
    struct node* tmp = m_front;
    struct node* new_node;
    U32 i;

    if (size() == 0)
        position = 0;
    else if (position > size())
        position = size();

    if (position == 0)
        return push_front(element);
    else if (position == size())
        return push_back(element);

    for (i = 0; i < position; ++i)
    {
        before = tmp;
        tmp = tmp->m_next;
    }

    new_node = new struct node(element, tmp);
    before->m_next = new_node;
}

template <typename T>
U32 LinkedList<T>::size()
{
    struct node* tmp = m_front;
    U32 current = 0;

    while (tmp != nullptr)
    {
        tmp = tmp->m_next;
        current++;
    }

    return current;
}

template <typename T>
void LinkedList<T>::remove(U32 position)
{
    struct node* before = nullptr;
    struct node* tmp = m_front;
    U32 i;

    if (size() == 0)
        throw std::runtime_error("The list is empty");

    if (position >= size())
        throw std::runtime_error("The position asked is bigger than the size of the linked-list");

    for (i = 0; i < position; ++i)
    {
        before = tmp;
        tmp = tmp->m_next;
    }

    if (before == nullptr)
    {
        m_front = tmp->m_next;
        if (tmp == m_back)
            m_back = nullptr;
    }
    else
    {
        before->m_next = tmp->m_next;
        if (tmp->m_next == nullptr)
            m_back = before;
    }

    delete tmp;
}

template <typename T>
void LinkedList<T>::remove(const std::function<bool(U32, T)>& func)
{
    struct node* tmp = m_front;
    U32 size = this->size();
    U32 current;

    for (current = 0; current < size; ++current)
    {
        if (func(current, tmp->m_data))
        {
            remove(current);
            current--;
            size--;
        }

        tmp = tmp->m_next;
    }
}

template <typename T>
void LinkedList<T>::remove(LinkedList<T>::Iterator it)
{
}

template <typename T>
T LinkedList<T>::get(U32 position)
{
    struct node* tmp = m_front;
    U32 i;

    if (size() <= position)
        throw std::runtime_error("The position asked is bigger than the size of the linked-list");

    for (i = 0; i < position; ++i)
    {
        tmp = tmp->m_next;
    }

    return tmp->m_data;
}

template <typename T>
T LinkedList<T>::front()
{
    if (size() == 0)
        throw std::runtime_error("Size is 0 but the front element is asked");

    return m_front->m_data;
}

template <typename T>
T LinkedList<T>::back()
{
    if (size() == 0)
        throw std::runtime_error("Size is 0 but the back element is asked");

    return m_back->m_data;
}

template <typename T>
void LinkedList<T>::execute(const std::function<void(U32, T*)>& func)
{
    struct node* tmp = m_front;
    U32 current = 0;
    U32 size = this->size();

    for (current = 0; current < size; ++current)
    {
        func(current, &(tmp->m_data));
        tmp = tmp->m_next;
    }
}

template <typename T>
void LinkedList<T>::execute(const std::function<bool(U32, T*)>& func)
{
    struct node* tmp = m_front;
    U32 current = 0;
    U32 size = this->size();

    for (current = 0; current < size; ++current)
    {
        if (!func(current, &(tmp->m_data)))
        {
            break;
        }
        tmp = tmp->m_next;
    }
}

template <typename T>
T LinkedList<T>::random()
{
    struct node* tmp = m_front;
    U32 current = 0;
    U32 pos;

    if (size() == 0)
        throw std::runtime_error("Size is 0 but a random element is asked");

    pos = rand() % size();

    for (current = 0; current < pos; ++current)
    {
        tmp = tmp->m_next;
    }

    return tmp->m_data;
}

template <typename T>
std::pair<bool, U32> LinkedList<T>::find(T needle)
{
    struct node* tmp = m_front;
    U32 size = this->size();
    U32 current = 0;

    for (current = 0; current < size; ++current)
    {
        if (tmp->m_data == needle)
            return std::make_pair(true, current);

        tmp = tmp->m_next;
    }

    return std::make_pair(false, 0);
}

template <typename T>
std::pair<bool, U32> LinkedList<T>::find_back(T needle)
{
    U32 current = size() - 1;

    for (; current > 0; --current)
    {
        if (get(current) == needle)
            return std::make_pair(true, current);
    }

    if (m_front != nullptr && m_front->m_data == needle)
        return std::make_pair(true, 0);

    return std::make_pair(false, 0);
}

template <typename T>
std::pair<bool, U32*> LinkedList<T>::find_all(T needle)
{
    return find_all([needle](U32 current, T* data){
        return *data == needle;
    });
}

template <typename T>
std::pair<bool, U32*> LinkedList<T>::find_all(const std::function<bool(U32, T*)>& func)
{
    struct node* tmp = m_front;
    U32 size = this->size();
    U32 current = 0;
    U32 count = 0;
    U32* result;

    for (current = 0; current < size; ++current)
    {
        if (func(current, &(tmp->m_data)))
        {
            count++;
        }

        tmp = tmp->m_next;
    }

    if (count == 0)
        return std::make_pair(false, nullptr);

    result = new U32[count];

    tmp = m_front;
    count = 0;
    for (current = 0; current < size; ++current)
    {
        if (func(current, &(tmp->m_data)))
        {
            result[count++] = current;
        }

        tmp = tmp->m_next;
    }

    return std::make_pair(false, result);
}

template <typename T>
void LinkedList<T>::sort(const std::function<bool(T*, T*)>& comparator)
{

}
