#include "event_handler.h"

#include "simple_db/net/poller/event.h"
#include <stdlib.h>


BEGIN_SIMPLE_DB_NS(net)

void EventHandler::HandleEvent(int event)
{
    if ((event & Event::ErrorEvent)) {
        if (mErrorCallback) {
            mErrorCallback();            
        }
        return;
    }
    
    if ((event & Event::ReadEvent) && mReadCallback) {
        mReadCallback();
    }

    if ((event & Event::WriteEvent) && mWriteCallback) {
        mWriteCallback();
    }

}


END_SIMPLE_DB_NS(net)

