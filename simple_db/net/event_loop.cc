#include "event_loop.h"

#include <stdlib.h>

#include "simple_db/net/poller/select_poller.h"

BEGIN_SIMPLE_DB_NS(net)

EventLoop::EventLoop()
{
}
EventLoop::~EventLoop()
{
}

bool EventHandler::Init()
{
    char *p = getenv(POLLER.c_str());
    if (p == nullptr) {
        p = "select";
    }
    std::string pollerType(p);

    if (pollerType == "select") {
        mPoller = new SelectPoller();
        return true;
    }
    return false;
}

bool EventHandler::AddAcceptHanlder(EventHandler *handler)
{
    if (handler == nullptr) {
        LOG_ERROR << "Handler is nullptr, add failed";
        return false;
    }

    if (mHandlerMap.find(handler->mFd == mHandlerMap.end())) {
        LOG_INFO << "Add handler " << handler->mFd;
        return true;
    }
    LOG_ERROR << "Hanlder " << handler->mFd << "already exist";
    return false;
}

void EventHandler::RemoveHandler(EventHandler *handler)
{
    if (handler == nullptr) {
        LOG_INFO << "Handler is nullptr ,do nothing";
        return ;
    }

    auto it = mHandlerMap.find(handler->mFd);
    if (it != mHandlerMap.end()) {
        mhandlerMap.erase(it);
    }
    SIMPLE_DB_DELETE_AND_SET_NULL(handler);
}

void EventHandler::LoopOnce()
{
    
}

END_SIMPLE_DB_NS(net)

