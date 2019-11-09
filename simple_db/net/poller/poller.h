#ifndef SIMPLE_DB_POLLER_H
#define SIMPLE_DB_POLLER_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(poller)

class EventLoop;
class EventHandler;

class Poller {
public:
    Poller();
    virtual ~Poller();
private:
    Poller(const Poller&);
    Poller& operator=(const Poller&);

public:
    static Poller* CreatePoller(EventLoop *eventLoop);

public:
    virtual int AddHandler(EventHandler *handler) = 0;
    virtual void RemoveHandler(EventHandler *handler) = 0;
    virtual void LoopOnce(int timeousMs, std::vector<EventHandler *> &handlers);

};

END_SIMPLE_DB_NS(poller)

#endif
