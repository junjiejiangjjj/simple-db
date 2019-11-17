#ifndef SIMPLE_DB_EVENT_LOOP_H
#define SIMPLE_DB_EVENT_LOOP_H

#include "simple_db/common/common.h"
#include "event_handler.h"
#include <map>
#include <mutex>
#include <atomic>

BEGIN_SIMPLE_DB_NS(net)

class EventHandler;
class Poller;

class EventLoop final {
private:
    explicit EventLoop(Poller *poller);
    ~EventLoop();
    
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);

public:
    static EventLoop* GetInstance();

private:
    void LoopOnce();
    

public:
    void Start();
    bool AddHandler(EventHandler *handler, int event);
    void RemoveHandler(EventHandler *handler);
    void Stop();


private:
    static std::once_flag initFlag;
    static void CreateInstance();
    static EventLoop* mEventLoop;
    

private:
    mutable std::mutex mMutex;
    std::atomic<bool> mIsRunning;
    std::map<int, EventHandler*> mHandlerMap;
    Poller *mPoller;

private:
    class GC{
    public:
        ~GC() {
            SIMPLE_DB_DELETE_AND_SET_NULL(EventLoop::mEventLoop);
        }
    };
    static GC gc;
    
};

END_SIMPLE_DB_NS(net)

#endif
