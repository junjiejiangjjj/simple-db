#include "tcp_server.h"
#include "simple_db/net/poller/event.h"
#include "simple_db/net/connector.h"
#include "simple_db/net/net_util.h"
#include <netinet/in.h>
#include <string.h>



BEGIN_SIMPLE_DB_NS(net)

TCPServer::TCPServer()
{
    mEventLoop = EventLoop::GetInstance();;
}

TCPServer::~TCPServer()
{
}

bool TCPServer::Bind(int port)
{
    mListenFd = NetUtil::Bind(port);
    if (mListenFd == -1) {
        return false;
    }
    EventHandler * handler = new EventHandler();
    handler->SetFd(mListenFd);
    
    handler->SetReadCallback(std::bind(&TCPServer::Accept, this));
    mEventLoop->AddHandler(handler, Event::ReadEvent);
    return true;
}

void TCPServer::RemoveConn(Connector *conn)
{
    mConnectorMap.erase(conn->GetFd());
    SIMPLE_DB_DELETE_AND_SET_NULL(conn);
}

void TCPServer::Accept()
{
    LOG_INFO << "Do accept";
    int connfd = NetUtil::Accept(mListenFd, nullptr, nullptr);
    LOG_INFO << "New connfd " << connfd;

    Connector *conn = new Connector(connfd);
    conn->SetCloseCallback(std::bind(&TCPServer::RemoveConn, this, conn));
    conn->SetReadCallback(mOnMessage);
    conn->Connect();
    mConnectorMap[connfd] = conn;
}

void TCPServer::SetOnMessage(const MsgCallback &cb)
{
    mOnMessage = cb;
}

void TCPServer::Start()
{
    mEventLoop->Start();
}

END_SIMPLE_DB_NS(net)

