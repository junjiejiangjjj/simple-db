#ifndef SIMPLE_DB_EVENT_LOOP_H
#define SIMPLE_DB_EVENT_LOOP_H

#include "simple_db/common/common.h"
#include <event_handler.h>
#include <map>

BEGIN_SIMPLE_DB_NS(net)

class EventHandler;
class Poller;

class EventLoop {
public:
    EventLoop();
    virtual ~EventLoop();
    
private:
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);

public:
    bool Init();
    void LoopOnce();
    bool AddHandler(EventHandler *handler);
    void RemoveHandler(EventHandler *handler);

private:
    std::map<EventHandler::HandlerFd, EventHandler*> mHandlerMap;
    Poller *mPoller;
    
};

END_SIMPLE_DB_NS(net)

#endif
