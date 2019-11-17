#include "event_handler.h"

#include "simple_db/net/poller/event.h"
#include <stdlib.h>


BEGIN_SIMPLE_DB_NS(net)

void EventHandler::HandleEvent(int event)
{
    if ((event & Event::ReadEvent) && mReadCallback) {
        mReadCallback();
    }

    if ((event & Event::WriteEvent) && mWriteCallback) {
        mWriteCallback();
    }

    if ((event & Event::ErrorEvent) && mErrorCallback) {
        mErrorCallback();
    }    
}



END_SIMPLE_DB_NS(net)

