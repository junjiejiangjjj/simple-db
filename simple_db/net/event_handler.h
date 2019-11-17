#ifndef SIMPLE_DB_EVENT_HANDLER_H
#define SIMPLE_DB_EVENT_HANDLER_H

#include "simple_db/common/common.h"

#include <functional>
#include <unistd.h>

BEGIN_SIMPLE_DB_NS(net)


class EventHandler {
public:
    typedef std::function<void()> EventCallback;
    
public:
    EventHandler() {}
    virtual ~EventHandler() { if (mFd) close(mFd); }
    
private:
    EventHandler(const EventHandler&);
    EventHandler& operator=(const EventHandler&);

public:
    void SetReadCallback(const EventCallback &cb) { mReadCallback = cb; }
    void SetWriteCallback(const EventCallback &cb) { mWriteCallback = cb; }
    void SetErrorCallback(const EventCallback &cb) { mErrorCallback = cb; }

public:
    void SetFd(int fd) { mFd=fd; }
    int GetHandlerFd() const { return mFd; }
    void HandleEvent(int event);

private:
    EventCallback mWriteCallback;
    EventCallback mErrorCallback;
    EventCallback mReadCallback;
    
private:
    int mFd;
};


END_SIMPLE_DB_NS(net)

#endif
