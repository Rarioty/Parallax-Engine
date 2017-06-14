template <class F, class... Args>
auto ThreadPool::addTask(F&& function, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;
    std::future<return_type> futureResult;

    if (this->m_status.load(std::memory_order_release) == state::STOP)
        throw std::runtime_error("Can't add task on stopped ThreadPool");

    auto packagedTask = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(function), std::forward<Args>(args)...)
    );

    futureResult = packagedTask->get_future();

    {
        std::lock_guard<std::mutex> guard(this->m_taskMutex);
        this->m_taskContainer.emplace([this, packagedTask]() { (*packagedTask)(); });
    }

    this->startTask();

    return futureResult;
}
