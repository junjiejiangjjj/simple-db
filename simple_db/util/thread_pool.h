#ifndef SIMPLE_DB_THREAD_POOL_H
#define SIMPLE_DB_THREAD_POOL_H

#include <future>
#include <atomic>
#include <deque>
#include <functional>

#include "simple_db/common/common.h"


BEGIN_SIMPLE_DB_NS(util)



class ThreadPool {
    using Task = std::function<void()>;

public:
    ThreadPool(size_t size);
    virtual ~ThreadPool();
    
private:
    ThreadPool(const ThreadPool&);
    ThreadPool& operator=(const ThreadPool&);

public:
    void AddTask(Task task);

    void Stop();
    void Start();
    bool Empty();

private:
    void Worker() {
        while (!mStop) {
            Task task;
            {
                std::unique_lock<std::mutex> lock(mMutex);
                if (!mStop && mTasks.empty()) {
                    mNotEmpty.wait(lock, [this]{return !mTasks.empty() || mStop;});
                }
            
                if (mTasks.empty())
                    continue;
                
                task = std::move(mTasks.front());
                mTasks.pop_front();                
            }
            task();
        }
    }

private:
    const size_t mThreadCount;
    std::atomic_bool mStop;        
    std::mutex mMutex;
    std::condition_variable mNotEmpty;

    
    std::deque<Task> mTasks;
    std::vector<std::thread> mThreads;

    
};


END_SIMPLE_DB_NS(util)

#endif
