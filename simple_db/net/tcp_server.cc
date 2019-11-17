#include "tcp_server.h"
#include "simple_db/net/poller/event.h"
#include "simple_db/net/connector.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


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
    struct sockaddr_in seraddr;
    bzero(&seraddr, sizeof(seraddr));
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);
    if (bind(fd, (sockaddr *)&seraddr, sizeof(seraddr)) != 0) {
        return false;
    }
    if (listen(fd, 128) != 0) {
        return false;
    }
    int option = fcntl(fd, F_GETFL, 0);
    option |= O_NONBLOCK;
    fcntl(fd, F_SETFL, option);
    
    EventHandler * handler = new EventHandler();
    handler->SetFd(fd);
    mListenFd = fd;
    
    handler->SetReadCallback(std::bind(&TCPServer::Accept, this));
    mEventLoop->AddHandler(handler, Event::ReadEvent);
    return true;
}

void TCPServer::RemoveConn(Connector *conn)
{
    mConnectorMap.erase(conn->GetFd());
    SIMPLE_DB_DELETE_AND_SET_NULL(conn);
}

int TCPServer::Accept()
{
    LOG_INFO << "Do accept";
    int connfd = accept(mListenFd, nullptr, nullptr);
    LOG_INFO << "New connfd " << connfd;

    Connector *conn = new Connector(connfd);
    conn->SetCloseCallback(std::bind(&TCPServer::RemoveConn, this, conn));
    conn->Connect();
    mConnectorMap[connfd] = conn;
}

bool TCPServer::Start()
{
    mEventLoop->Start();
}

END_SIMPLE_DB_NS(net)

