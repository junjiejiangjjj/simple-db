#ifndef SIMPLE_DB_POLLER_H
#define SIMPLE_DB_POLLER_H

#include "simple_db/common/common.h"
#include "simple_db/net/poller/event.h"


BEGIN_SIMPLE_DB_NS(net)


class Poller {
public:
    Poller();
    virtual ~Poller();
private:
    Poller(const Poller&);
    Poller& operator=(const Poller&);

public:
    static Poller* CreatePoller(const std::string &pollerName);

public:
    virtual void Update(int fd, int event) = 0;
    virtual void Unregister(int fd) = 0;
    virtual void Poll(int timeousMs, std::map<int, int> &fdMap) = 0;
};


END_SIMPLE_DB_NS(net)

#endif
