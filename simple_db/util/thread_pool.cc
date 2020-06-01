#include "thread_pool.h"

BEGIN_SIMPLE_DB_NS(util)

ThreadPool::ThreadPool(size_t size): mThreadCount(size),
    mStop(false), mMutex(), mNotEmpty()
{
}

ThreadPool::~ThreadPool()
{
    Stop();
}

void ThreadPool::Stop()
{
    mStop = true;
    mNotEmpty.notify_all();
    for (auto &t: mThreads) {
        t.join();
    }
}

void ThreadPool::Start()
{
    for (size_t i = 0; i < mThreadCount; ++i) {
        mThreads.push_back(std::thread(&ThreadPool::Worker, this));
    }
}


void ThreadPool::AddTask(Task task)
{
    if (!mStop) {
        std::lock_guard<std::mutex> lock(mMutex);
        mTasks.emplace_back(task);
        mNotEmpty.notify_one();
    }
}

bool ThreadPool::Empty()
{
    std::lock_guard<std::mutex> lock(mMutex);
    return mTasks.empty();
}


END_SIMPLE_DB_NS(util)

