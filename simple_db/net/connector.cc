#include "connector.h"
#include "simple_db/net/event_loop.h"
#include "simple_db/net/poller/event.h"
#include "simple_db/net/net_util.h"
#include "simple_db/net/socket_opt.h"

BEGIN_SIMPLE_DB_NS(net)

Connector::Connector(int fd)
{
    NetUtil::SetNoBlock(fd);
    mConnFd = fd;
    mEventLoop = EventLoop::GetInstance();
}

Connector::~Connector()
{
    mEventLoop->RemoveHandler(mHandler);    
    if (mCloseCallback)
        mCloseCallback();
}

bool Connector::Connect()
{
    mHandler = new EventHandler();
    mHandler->SetFd(mConnFd);
    mHandler->SetReadCallback(std::bind(&Connector::Read, this));
    mEventLoop->AddHandler(mHandler, Event::ReadEvent);
    return true;
}

void Connector::Read()
{
    SocketOpt opt(mConnFd);
    mReadCallback(&opt);
    mEventLoop->RemoveHandler(mHandler);
}

END_SIMPLE_DB_NS(net)

