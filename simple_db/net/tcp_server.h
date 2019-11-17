#ifndef SIMPLE_DB_TCP_SERVER_H
#define SIMPLE_DB_TCP_SERVER_H

#include "simple_db/common/common.h"
#include "simple_db/net/event_loop.h"

#include <sys/socket.h>
#include <netinet/in.h>


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

private:
    int Accept();

public:
    bool Start();
    void Stop();
        
private:
    EventLoop *mEventLoop;
    std::map<int, Connector*> mConnectorMap;
    int mListenFd;
};

END_SIMPLE_DB_NS(net)

#endif
