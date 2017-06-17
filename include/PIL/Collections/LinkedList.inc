template <typename T>
LinkedListIterator<T>::LinkedListIterator()
    : m_current_node(nullptr)
{}

template <typename T>
LinkedListIterator<T>::LinkedListIterator(struct LinkedList<T>::node* node)
    : m_current_node(node)
{}

template <typename T>
LinkedListIterator<T>::~LinkedListIterator()
{}

template <typename T>
T LinkedListIterator<T>::operator*()
{
    return m_current_node->m_data;
}

template <typename T>
void LinkedListIterator<T>::next()
{
    m_current_node = m_current_node->m_next;
}

template <typename T>
void LinkedListIterator<T>::operator++()
{
    return this->next();
}

template <typename T>
bool LinkedListIterator<T>::operator!=(LinkedListIterator<T> it)
{
    return this->m_current_node != it.m_current_node;
}

template <typename T>
bool LinkedListIterator<T>::operator==(LinkedListIterator<T> it)
{
    return this->m_current_node == it.m_current_node;
}

template <typename T>
LinkedList<T>::LinkedList()
{
    m_front = m_back = nullptr;
    m_current_size = 0;
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
    return LinkedListIterator<T>(m_front);
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::end()
{
    return LinkedListIterator<T>(nullptr);
}

template <typename T>
void LinkedList<T>::push_front(T element)
{
    struct node* new_node = new struct node(element, m_front);

    if (m_front == nullptr)
        m_back = new_node;

    m_front = new_node;

    m_current_size++;
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

    m_current_size++;
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

    m_current_size++;
}

template <typename T>
U32 LinkedList<T>::size()
{
    return m_current_size;
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
    m_current_size--;
}

template <typename T>
void LinkedList<T>::remove(const std::function<bool(U32, T)>& func)
{
    struct node* tmp = m_front;
    U32 size = this->size();
    U32 current;

    for (current = 0; current < size; ++current)
    {
        bool result = func(current, tmp->m_data);
        tmp = tmp->m_next;

        if (result)
        {
            remove(current);
            current--;
            size--;
        }
    }
}

template <typename T>
void LinkedList<T>::remove(LinkedList<T>::Iterator it)
{
    U32 pos = it.m_current;

    remove(pos);
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
void LinkedList<T>::swap(U32 first, U32 second)
{
    if (first >= size() || second >= size())
        throw std::runtime_error("Elements to swap are too far in the container");

    if (first == second)
        return;
    else if (second < first)
        return swap(second, first);

    struct node* before_second = nullptr;
    struct node* before_first = nullptr;
    struct node* second_node = nullptr;
    struct node* first_node = nullptr;
    struct node* before = nullptr;
    struct node* tmp = m_front;
    U32 current;

    for (current = 0; current < size(); ++current)
    {
        if (current == first)
        {
            before_first = before;
            first_node = tmp;
        }
        else if (current == second)
        {
            before_second = before;
            second_node = tmp;
        }

        if (first_node != nullptr && second_node != nullptr)
            break;

        before = tmp;
        tmp = tmp->m_next;
    }

    if (before_first != nullptr)
        before_first->m_next = second_node;
    else
        m_front = second_node;

    tmp = second_node->m_next;
    if (first_node->m_next != second_node)
        second_node->m_next = first_node->m_next;
    else
        second_node->m_next = first_node;

    before_second->m_next = first_node;
    first_node->m_next = tmp;
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
struct LinkedList<T>::node* partition(
    struct LinkedList<T>::node* head, struct LinkedList<T>::node* end,
    struct LinkedList<T>::node** new_head, struct LinkedList<T>::node** new_end,
    const std::function<bool(T, T)>& comparator)
{
    struct LinkedList<T>::node* pivot = end;
    struct LinkedList<T>::node* prev = nullptr;
    struct LinkedList<T>::node* tail = pivot;
    struct LinkedList<T>::node* cur = head;

    while (cur != pivot)
    {
        if (comparator(cur->m_data, pivot->m_data))
        {
            if ((*new_head) == nullptr)
                (*new_head) = cur;

            prev = cur;
            cur = cur->m_next;
        }
        else
        {
            if (prev)
                prev->m_next = cur->m_next;
            struct LinkedList<T>::node* tmp = cur->m_next;
            cur->m_next = nullptr;
            tail->m_next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if ((*new_head) == nullptr)
        *(new_head) = pivot;

    (*new_end) = tail;

    return pivot;
}

template <typename T>
struct LinkedList<T>::node* quicksort(
    struct LinkedList<T>::node* head, struct LinkedList<T>::node* end,
    const std::function<bool(T, T)>& comparator)
{
    if (head == nullptr || head == end)
        return head;

    struct LinkedList<T>::node* new_head = nullptr;
    struct LinkedList<T>::node* new_end = nullptr;

    struct LinkedList<T>::node* pivot = partition(head, end, &new_head, &new_end, comparator);

    if (new_head != pivot)
    {
        struct LinkedList<T>::node* tmp = new_head;
        while (tmp->m_next != pivot)
            tmp = tmp->m_next;
        tmp->m_next = nullptr;

        new_head = quicksort(new_head, tmp, comparator);

        tmp = new_head;
        while (tmp != nullptr && tmp->m_next != nullptr)
            tmp = tmp->m_next;
        tmp->m_next = pivot;
    }

    pivot->m_next = quicksort(pivot->m_next, new_end, comparator);

    return new_head;
}

template <typename T>
void LinkedList<T>::sort(const std::function<bool(T, T)>& comparator)
{
    m_front = quicksort(m_front, m_back, comparator);
}
