#include "tcp_server.h"
#include <string.h>
#include <unistd.h>


BEGIN_SIMPLE_DB_NS(net)

TCPServer::TCPServer()
{
    mListenFd = -1;
    bzero(&mServaddr, sizeof(mServaddr));
    mStart = false;
    mNeedStop = false;
    mPoller = nullptr;
    for (int i = 0; i < 1024; i++) {
        mConnFd[i] = -1;
    }
}

TCPServer::~TCPServer()
{
    SIMPLE_DB_DELETE_AND_SET_NULL(mPoller);
}

bool TCPServer::Listen()
{
    if (listen(mListenFd, 128) != 0) {
        return false;
    }
    return true;
}

bool TCPServer::Bind(int port)
{
    mListenFd = socket(AF_INET, SOCK_STREAM, 0);
    mServaddr.sin_family = AF_INET;
    mServaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    mServaddr.sin_port = htons(port);
    if (bind(mListenFd, (sockaddr *)&mServaddr, sizeof(mServaddr)) != 0) {
        return false;
    }
    if (!Listen()) {
        return false;
    }
    return true;

}

void TCPServer::DoAccept()
{
    char* buf = new char[1000];
    ssize_t n = 0;
    for (int i = 0; i < 1024; i++) {
        if (mConnFd[i] < 0)
            continue;
        
        LOG_INFO << i << " " << mConnFd[i];
        int connfd = mConnFd[i];
        read(connfd, buf, (size_t)1000);
        LOG_INFO << buf;
        write(connfd, "Hello", 6);
        close(connfd);
        mPoller->Unregister(connfd);
        mConnFd[i] = -1;
        n = 0;
        memset(buf, 0, 1000);
    }
    delete buf;
    
}

int TCPServer::Accept()
{
    struct sockaddr_in childAddr;
    socklen_t children;
    int connfd = accept(mListenFd, (sockaddr *)&childAddr, &children);
    for (int i = 0; i < 1024; i++) {
        if (mConnFd[i] < 0) {
            mConnFd[i] = connfd;
            break;
        }
    }
    mPoller->Update(connfd, Event::ReadEvent);
    DoAccept();
 }

bool TCPServer::Start()
{
    if (mStart) {
        return false;
    }
    mStart = true;
    mPoller = Poller::CreatePoller("select");
    if (mPoller == nullptr) {
        LOG_ERROR << "Create poller failed";
        return false;
    }
    mPoller->Update(mListenFd, Event::ReadEvent);    
    while (!mNeedStop) {
        std::map<int, int> fdEventMap;
        mPoller->Poll(1000, fdEventMap);
        LOG_INFO << "Loop once " << fdEventMap.size();
        if (fdEventMap.find(mListenFd) != fdEventMap.end()) {
            LOG_INFO << "Do accept";
            Accept();
        }
    }
}

void TCPServer::Stop()
{
    mNeedStop = true;
}

END_SIMPLE_DB_NS(net)

