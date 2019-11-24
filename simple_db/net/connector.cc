#include "connector.h"
#include "simple_db/net/event_loop.h"
#include "simple_db/net/poller/event.h"

BEGIN_SIMPLE_DB_NS(net)

Connector::Connector(int fd)
{
    NetUtil::SetNoBlock(fd);
    mConnFd = fd;
    buf = new char[MAX_BUF_SIZE];
    mEventLoop = EventLoop::GetInstance();
}

Connector::~Connector()
{
    mEventLoop->RemoveHandler(mHandler);    
    if (mCloseCallback)
        mCloseCallback();
    delete[] buf;
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
    mReadCallback(mConnFd);
    mEventLoop->RemoveHandler(mHandler);
}

END_SIMPLE_DB_NS(net)

