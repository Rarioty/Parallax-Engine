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
void LinkedList<T>::push(T element)
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
void LinkedList<T>::remove(U32 position)
{
    struct node* before = nullptr;
    struct node* tmp = m_front;
    U32 i;

    if (size() <= position)
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
