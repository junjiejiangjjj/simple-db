#include "connector.h"
#include "simple_db/net/event_loop.h"
#include "simple_db/net/poller/event.h"

BEGIN_SIMPLE_DB_NS(net)

Connector::Connector(int fd)
{
    mConnFd = fd;
    buf = new char[MAX_BUF_SIZE];
    mEventLoop = EventLoop::GetInstance();
}

Connector::~Connector()
{
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
    int n = read(mConnFd, buf, MAX_BUF_SIZE);
    LOG_INFO << buf;
    write(mConnFd, "hello", 6);
    mEventLoop->RemoveHandler(mHandler);
    mCloseCallback();
}

END_SIMPLE_DB_NS(net)

