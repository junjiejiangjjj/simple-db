#include "poller.h"
#include "select_poller.h"

BEGIN_SIMPLE_DB_NS(net)

Poller::Poller()
{
}
Poller::~Poller()
{
}

/* static */ Poller* Poller::CreatePoller(const std::string &pollerName)
{
    Poller* poller = new SelectPoller();
    return poller;
}

END_SIMPLE_DB_NS(net)

