#include "simple_db/net/event_handler.h"


BEGIN_SIMPLE_DB_NS(net)


EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void AddHandler(EventHandler *handler)
{
    if (handler == nullptr) {
        
    }
}

END_SIMPLE_DB_NS(net)
