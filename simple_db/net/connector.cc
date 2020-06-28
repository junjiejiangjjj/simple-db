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
    LOG_INFO << "Do destroy connector";
    mEventLoop->RemoveHandler(mHandler);
    SIMPLE_DB_DELETE_AND_SET_NULL(mHandler);
}

bool Connector::Connect()
{
    mHandler = new EventHandler();
    mHandler->SetFd(mConnFd);
    mHandler->SetReadCallback([&] { this->Read(); });
    mHandler->SetErrorCallback([&] { this->Close(); });
    mEventLoop->AddHandler(mHandler, Event::ReadEvent);
    return true;
}

void Connector::Read()
{
    SocketOpt opt(mConnFd);
    mReadCallback(&opt);
}

void Connector::Close()
{
    if (mCloseCallback)
        mCloseCallback();
}


END_SIMPLE_DB_NS(net)

