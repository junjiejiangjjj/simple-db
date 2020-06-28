#include "epoll.h"
#include <cstring>
#include <sys/epoll.h>
#include <unistd.h>


BEGIN_SIMPLE_DB_NS(net)

Epoll::Epoll(): mEpollFd(::epoll_create1(EPOLL_CLOEXEC)),
    mEvents(INIT_EVENT_LIST_SIZE)
{
    if (mEpollFd < 0) {
        LOG_ERROR << "Create epoll fd failed";
        abort();
    }
}

Epoll::~Epoll()
{
    ::close(mEpollFd);
}

void Epoll::Update(int fd, int event)
{
    LOG_INFO << "Update fd " << fd << " Event " << event;
    struct epoll_event ev;
    std::memset(&ev, 0, sizeof(ev));
    ev.data.fd = fd;
    
    if (event & Event::ReadEvent) {
        ev.events |= EPOLLIN;
    }
    if (event & Event::WriteEvent) {
        ev.events |= EPOLLOUT;
    }

    // ev.events |= EPOLLET;

    int ctlRet = 0;
    if (mFdSet.find(fd) == mFdSet.end()) {
        LOG_INFO << "Do add new fd " << fd;
        ctlRet = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, fd, &ev);
        mFdSet.insert(fd);
        
    } else {
        LOG_INFO << "Do update new fd " << fd;
        ctlRet = epoll_ctl(mEpollFd, EPOLL_CTL_MOD, fd, &ev);
    }
    if (ctlRet != 0) {
        LOG_ERROR << "Update fd " << fd << "failed, reason: " << std::strerror(errno);
    }
}

void Epoll::Unregister(int fd)
{
    LOG_INFO << "Unregister fd " << fd;
    auto it = mFdSet.find(fd);
    if (it == mFdSet.end()) {
        LOG_ERROR << "Fd " << fd << " not in epoll set";
        return ;
    }
    mFdSet.erase(it);
    
    struct epoll_event ev;
    if (epoll_ctl(mEpollFd, EPOLL_CTL_DEL, fd, &ev) != 0) {
        LOG_ERROR << "Delete fd " << fd << "failed, reason: " << std::strerror(errno);        
    }
}

void Epoll::Poll(int timeousMs, std::map<int, int> &fdMap)
{

    int num = ::epoll_wait(mEpollFd, &mEvents[0], INIT_EVENT_LIST_SIZE, timeousMs);
    if (num < 0) {
        return;
    }

    for (int i = 0; i < num; ++i) {
        int event = Event::NoneEvent;
        if ((EPOLLIN) & mEvents[i].events) {
            event |= Event::ReadEvent;
        }
        if (EPOLLOUT & mEvents[i].events) {
            event |= Event::WriteEvent;
        }
        if ((EPOLLHUP | EPOLLERR) & mEvents[i].events) {
            event |= Event::ErrorEvent;
        }
        if (event != Event::NoneEvent) {
            fdMap[mEvents[i].data.fd] = event;            
        }
    }
}

END_SIMPLE_DB_NS(net)

