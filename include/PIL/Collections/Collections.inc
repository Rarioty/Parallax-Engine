template <typename T>
Container<T>::Container()
{}

template <typename T>
Container<T>::~Container()
{}

template <typename T>
void Container<T>::push_front(T& element)
{}

template <typename T>
void Container<T>::push_back(T& element)
{}

template <typename T>
void Container<T>::insert(T& element, U32 position)
{}

template <typename T>
void Container<T>::remove(const std::function<bool()>& func)
{}

template <typename T>
T Container<T>::front()
{}

template <typename T>
T Container<T>::back()
{}

template <typename T>
void Container<T>::execute(const std::function<void(U32, T*)>& func)
{}

template <typename T>
void Container<T>::execute(const std::function<bool(U32, T*)>& func)
{}

template <typename T>
T Container<T>::random()
{}

template <typename T>
U32 Container<T>::find(T& needle)
{}

template <typename T>
U32 Container<T>::find_back(T& needle)
{}

template <typename T>
U32* Container<T>::find_all(T& needle)
{}

template <typename T>
U32* Container<T>::find_all(const std::function<bool(U32, T*)>& func)
{}

template <typename T>
void Container<T>::sort(const std::function<bool(T*, T*)>& func)
{}
