#ifndef SIMPLE_DB_CONNECTOR_H
#define SIMPLE_DB_CONNECTOR_H

#include "simple_db/common/common.h"
#include "simple_db/net/callback_base.h"
#include <functional>

BEGIN_SIMPLE_DB_NS(net)

class EventLoop;
class EventHandler;

class Connector {
public:
    explicit Connector(int fd);
    virtual ~Connector();
private:
    Connector(const Connector&);
    Connector& operator=(const Connector&);

public:
    void Read();
    void Close();
    // void Write(const std::string &data);
    // void Write(const char* data);    
    void SetCloseCallback(const Callback &cb) { mCloseCallback = cb; }
    void SetReadCallback(const MsgCallback &cb) { mReadCallback = cb; }     
    bool Connect();
    int GetFd() const { return mConnFd; }

private:
    int mConnFd;
    Callback mCloseCallback;
    MsgCallback mReadCallback;
    
    EventLoop *mEventLoop;
    EventHandler *mHandler;
};

END_SIMPLE_DB_NS(net)

#endif
