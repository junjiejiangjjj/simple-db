#ifndef SIMPLE_DB_EPOLL_H
#define SIMPLE_DB_EPOLL_H

#include <set>
#include "simple_db/net/poller/poller.h"
#include "simple_db/common/common.h"

struct epoll_event;

BEGIN_SIMPLE_DB_NS(net)

class Epoll final: public Poller{
public:
    Epoll();
    virtual ~Epoll();
private:
    Epoll(const Epoll&) = delete;
    Epoll& operator=(const Epoll&) = delete;

public:
    void Update(int fd, int event) override;
    void Unregister(int fd) override;
    void Poll(int timeousMs, std::map<int, int> &fdMap);

private:
    typedef std::vector<struct epoll_event> EventList;
    
    static const int INIT_EVENT_LIST_SIZE = 16;
    int mEpollFd;
    EventList mEvents;
    std::set<int> mFdSet;
};

END_SIMPLE_DB_NS(net)

#endif
