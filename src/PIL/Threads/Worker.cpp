#include <PIL/Threads/Worker.hpp>

namespace Parallax::Threads
{
    Worker::Worker()
        : m_task(nullptr)
        , m_thread()
        , m_running(false)
        , m_reserved(false)
    {}

    Worker::~Worker()
    {
        if (this->m_running.load())
            this->stop();

        this->waitStopped();
    }

    void Worker::start(const Task& task)
    {
        if (this->m_running.load() == true)
            throw std::runtime_error("Can't start an already running worker");
        this->m_running.store(true);
        this->m_thread = std::thread(task);
    }

    void Worker::start(std::condition_variable& cv, std::mutex& condvarMutex)
    {
        if (this->m_running.load() == true)
            throw std::runtime_error("Can't start an already running worker");
        this->m_running.store(true);
        this->m_thread = std::thread(&Worker::threadMain, this, std::ref(cv), std::ref(condvarMutex));
    }

    void Worker::stop()
    {
        this->m_running.store(false);
    }

    void Worker::stopTask()
    {
        std::lock_guard<std::mutex> guard(this->m_taskMutex);
        if (this->m_task != nullptr)
            this->m_task.stop();
    }

    void Worker::pauseTask()
    {
        std::lock_guard<std::mutex> guard(this->m_taskMutex);
        if (this->m_task != nullptr)
            this->m_task.pause();
    }

    void Worker::unpauseTask()
    {
        std::lock_guard<std::mutex> guard(this->m_taskMutex);
        if (this->m_task != nullptr)
            this->m_task.unpause();
    }

    void Worker::waitStopped()
    {
        if (this->m_thread.joinable())
            this->m_thread.join();
    }

    void Worker::threadMain(std::condition_variable& cv, std::mutex& condvarMutex)
    {
        while (this->m_running.load())
        {
            {
                std::unique_lock<std::mutex> lock(condvarMutex);

                cv.wait(lock,
                    [this] {
                        std::lock_guard<std::mutex> guard(this->m_taskMutex);
                        return (not this->m_running.load() || this->m_task != nullptr);
                    });

                if (not this->m_running.load()) return;
            }

            this->m_task();
            this->setReserved(false);
            this->setTask(Task(nullptr));
        }
    }

    void Worker::setTask(const std::function<void()>& task)
    {
        std::lock_guard<std::mutex> taskGuard(this->m_taskMutex);
        this->m_task = task;
    }

    void Worker::setTask(const Task& task)
    {
        std::lock_guard<std::mutex> taskGuard(this->m_taskMutex);
        this->m_task = task;
    }

    bool Worker::isIdle()
    {
        std::lock_guard<std::mutex> taskGuard(this->m_taskMutex);
        return (this->m_task == nullptr);
    }

    void Worker::setReserved(bool status)
    {
        this->m_reserved.store(status);
    }

    bool Worker::isReserved()
    {
        return this->m_reserved.load();
    }
}
