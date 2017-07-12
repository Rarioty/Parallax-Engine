template <typename T>
bool Task::operator==(const T& var)
{
    return (m_function == var);
}

template <typename T>
bool Task::operator!=(const T& var)
{
    return (m_function != var);
}

template <class F, class... Args>
auto Task::assign(F&& function, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(function), std::forward<Args>(args)...)
    );
    auto future = task->get_future();

    this->m_function = [this, task]() { (*task)(); };

    return future;
}

template <class F, class... Args>
void Task::addCallback(F&& function, Args&&... args)
{
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);
    auto wrappedTask = [this, task]() { task(); };

    std::lock_guard<std::mutex> lock_guard(m_callbackMutex);
    m_callbacks.emplace_back(wrappedTask);
}

template <class F, class... Args>
void Task::setStopFunction(F&& function, Args&&... args)
{
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);

    this->m_stopFunction = [this, task]() { task(); };
}

template <class F, class... Args>
void Task::setPauseFunction(F&& function, Args&&... args)
{
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);

    this->m_pauseFunction = [this, task]() { task(); };
}

template <class F, class... Args>
void Task::setUnPauseFunction(F&& function, Args&&... args)
{
    auto task = std::bind(std::forward<F>(function), std::forward<Args>(args)...);

    this->m_unpauseFunction = [this, task]() { task(); };
}
