#ifndef SIMPLE_DB_TCP_SERVER_H
#define SIMPLE_DB_TCP_SERVER_H

#include "simple_db/common/common.h"
#include "simple_db/net/poller/poller.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <atomic>


BEGIN_SIMPLE_DB_NS(net)

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

private:
    int Accept();
    void DoAccept();

public:
    bool Start();
    void Stop();
        
private:
    Poller* mPoller;
    int mListenFd;
    int mConnFd[1024];
    struct sockaddr_in mServaddr;
    bool mStart;
    std::atomic<bool> mNeedStop;
};

END_SIMPLE_DB_NS(net)

#endif
