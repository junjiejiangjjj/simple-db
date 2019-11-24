#ifndef SIMPLE_DB_TCP_SERVER_H
#define SIMPLE_DB_TCP_SERVER_H

#include "simple_db/common/common.h"
#include "simple_db/net/event_loop.h"
#include "simple_db/net/callback_base.h"

BEGIN_SIMPLE_DB_NS(net)

class Connector;

class TCPServer final {
public:
    TCPServer();
    virtual ~TCPServer();

private:
    TCPServer(const TCPServer&);
    TCPServer& operator=(const TCPServer&);
    bool Listen();

public:
    bool Bind(int port);
    void RemoveConn(Connector*);
    void SetOnMessage(const MsgCallback &cb);

private:
    void Accept();

public:
    void Start();
    void Stop();
        
private:
    EventLoop *mEventLoop;
    std::map<int, Connector*> mConnectorMap;
    MsgCallback mOnMessage;
    int mListenFd;
};

END_SIMPLE_DB_NS(net)

#endif
