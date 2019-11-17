#ifndef SIMPLE_DB_CONNECTOR_H
#define SIMPLE_DB_CONNECTOR_H

#include "simple_db/common/common.h"
#include <functional>

BEGIN_SIMPLE_DB_NS(net)

class EventLoop;
class EventHandler;

class Connector {
public:
    typedef std::function<void()> CloseCallback;
public:
    explicit Connector(int fd);
    virtual ~Connector();
private:
    Connector(const Connector&);
    Connector& operator=(const Connector&);

public:
    void Read();
    void SetCloseCallback(const CloseCallback &cb) { mCloseCallback = cb; }
    bool Connect();
    int GetFd() const { return mConnFd; }

private:
    int mConnFd;
    CloseCallback mCloseCallback;
    EventLoop *mEventLoop;
    EventHandler *mHandler;
    static const size_t MAX_BUF_SIZE = 1024 * 1024;
    char* buf;
};

END_SIMPLE_DB_NS(net)

#endif
