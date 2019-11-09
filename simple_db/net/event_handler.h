#ifndef SIMPLE_DB_EVENT_HANDLER_H
#define SIMPLE_DB_EVENT_HANDLER_H

#include "simple_db/common/common.h"

#include <functional>

BEGIN_SIMPLE_DB_NS(net)

class EventHandler final{
public:
    typedef int HandlerFd;
    typedef std::function<void()> EventCallback;
    typedef std::function<void(size_t timeooutMs)> ReadEventCallback;

public:
    EventHandler();
    ~EventHandler();
private:
    EventHandler(const EventHandler&);
    EventHandler& operator=(const EventHandler&);

public:
    void SetReadCallback(ReadEventCallback &cb) { mReadCallback = cb; }
    void SetWriteCallback(EventCallback &cb) { mWriteCallback = cb; }
    void SetErrorCallback(EventCallback &cb) { mErrorCallback = cb; }


public:
    HandlerFd GetHandlerFd();
    // void HandleRead();
    // void HandleWrite();
    // void HandleError();

private:
    EventCallback mWriteCallback;
    EventCallback mErrorCallback;
    ReadEventCallback mReadCallback;

    HandlerFd mFd;
};

END_SIMPLE_DB_NS(net)

#endif
