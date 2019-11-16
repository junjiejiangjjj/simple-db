#ifndef SIMPLE_DB_SELECT_POLLER_H
#define SIMPLE_DB_SELECT_POLLER_H

#include "simple_db/common/common.h"

#include "simple_db/net/poller/poller.h"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>


BEGIN_SIMPLE_DB_NS(net)

class SelectPoller final : public Poller{
public:
    SelectPoller();
    ~SelectPoller();
private:
    SelectPoller(const SelectPoller&);
    SelectPoller& operator=(const SelectPoller&);

public:
    void Update(int fd, int event) override;
    void Unregister(int fd) override;
    void Poll(int timeousMs, std::map<int, int> &fdMap);

private:
    void ClearFd(int fd);
    void ClearSet();

private:
    // 记录事件
    fd_set mReadSet;
    fd_set mWriteSet;
    fd_set mErrorSet;

    // select 中用于存放有事件的fd
    fd_set mSelectReadSet;
    fd_set mSelectWriteSet;
    fd_set mSelectErrorSet;    

    std::map<int, int> mAllFdMap;
};

END_SIMPLE_DB_NS(net)

#endif
