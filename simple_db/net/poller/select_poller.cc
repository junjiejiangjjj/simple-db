#include "select_poller.h"

BEGIN_SIMPLE_DB_NS(net)

SelectPoller::SelectPoller()
{

    FD_ZERO(&mReadSet);
    FD_ZERO(&mWriteSet);
    FD_ZERO(&mErrorSet);
    FD_ZERO(&mSelectReadSet);
    FD_ZERO(&mSelectWriteSet);
    FD_ZERO(&mSelectErrorSet);    
}

SelectPoller::~SelectPoller()
{
}

void SelectPoller::Update(int fd, int event)
{
    LOG_INFO << "Update fd " << fd << " Event " << event;
    if (mAllFdMap.find(fd) == mAllFdMap.end()) {
        LOG_INFO << "Not find fd " << fd << " do add";
        mAllFdMap[fd] = event;
    }
    
    ClearFd(fd);
    if (event & Event::ReadEvent) {
        FD_SET(fd, &mReadSet);
    }
    if (event & Event::WriteEvent) {
        FD_SET(fd, &mWriteSet);        
    }
    if (event & Event::ErrorEvent) {
        FD_SET(fd, &mErrorSet);        
    }
    if (event == Event::NoneEvent) {
        mAllFdMap.erase(fd);
    }
}

void SelectPoller::Unregister(int fd)
{
    if (mAllFdMap.find(fd) == mAllFdMap.end()) {
        LOG_ERROR << "Fd " << fd << "not in set";
        return;
    }
    
    ClearFd(fd);
    mAllFdMap.erase(fd);
}

void SelectPoller::ClearFd(int fd)
{
    FD_CLR(fd, &mReadSet);
    FD_CLR(fd, &mReadSet);
    FD_CLR(fd, &mReadSet);
}

void SelectPoller::Poll(int timeoutMs, std::map<int, int> &fdMap)
{
    timeval waitTime;
    waitTime.tv_sec = timeoutMs / 1000;
    waitTime.tv_usec = 0;
    // map key默认按从小到大排序，最后一个元素key最大
    auto it = mAllFdMap.end();
    it--;
    int maxFd = it->first;
    mSelectReadSet = mReadSet;
    mSelectWriteSet = mWriteSet;
    mSelectErrorSet = mErrorSet;
    int ret = select(maxFd + 1, &mSelectReadSet, &mSelectWriteSet, &mSelectErrorSet, &waitTime);
    if (ret == -1) {
        LOG_ERROR << "Do select error " << errno;
        perror("select");
        return;
    }
    if (ret == 0) {
        return;
    }
    for (const auto &item: mAllFdMap) {
        int event = Event::NoneEvent;
        if (FD_ISSET(item.first, &mReadSet)) {
            event |= Event::ReadEvent;
        }
        if (FD_ISSET(item.first, &mWriteSet)) {
            event |= Event::WriteEvent;
        }
        if (FD_ISSET(item.first, &mErrorSet)) {
            event |= Event::ErrorEvent;
        }
        if (event != Event::NoneEvent) {
            fdMap[item.first] = event;            
        }
    }
}


END_SIMPLE_DB_NS(net)

