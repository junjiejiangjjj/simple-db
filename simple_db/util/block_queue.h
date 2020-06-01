#ifndef SIMPLE_DB_BLOCK_QUEUE_H
#define SIMPLE_DB_BLOCK_QUEUE_H

#include "simple_db/common/common.h"
#include <condition_variable>
#include <queue>
#include <mutex>

BEGIN_SIMPLE_DB_NS(util)


template<class T>
class BlockQueue {
public:
    BlockQueue(): mQueue(), mMutex(), mNotEmpty() {}
    ~BlockQueue() {};
    
private:
    BlockQueue(const BlockQueue&) = delete;
    BlockQueue& operator=(const BlockQueue&) = delete;

public:
    void Push(const T& item);
    void Push(T&& item);    
    T Take();
    bool Empty();
    size_t Size();

private:
    
    std::queue<T> mQueue;
    std::mutex mMutex;
    std::condition_variable mNotEmpty;
    
};


template<class T>
void BlockQueue<T>::Push(const T& item)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mQueue.push(item);
    mNotEmpty.notify_all();
}

template<class T>
void BlockQueue<T>::Push(T&& item)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mQueue.push(std::move(item));
    mNotEmpty.notify_one();
}


template<class T>
T BlockQueue<T>::Take()
{

    std::unique_lock<std::mutex> lock(mMutex);
    if (mQueue.empty()) {
        mNotEmpty.wait(lock, [this]{ return !mQueue.empty();});
    }

    assert(!mQueue.empty());
    
    T front = mQueue.front();
    mQueue.pop();
    return front;
}


template<class T>
bool BlockQueue<T>::Empty()
{
    std::lock_guard<std::mutex> lock(mMutex);
    return mQueue.empty();
}


template<class T>
size_t BlockQueue<T>::Size()
{
    std::lock_guard<std::mutex> lock(mMutex);
    return mQueue.size();
}
    



END_SIMPLE_DB_NS(util)

#endif
