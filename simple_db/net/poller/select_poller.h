#ifndef SIMPLE_DB_SELECT_POLLER_H
#define SIMPLE_DB_SELECT_POLLER_H

#include "simple_db/common/common.h"

#include "simple_db/net/poller/poller.h"
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>


BEGIN_SIMPLE_DB_NS(poller)

class SelectPoller : public Poller{
public:
    SelectPoller();
    ~SelectPoller();
private:
    SelectPoller(const SelectPoller&);
    SelectPoller& operator=(const SelectPoller&);
};

END_SIMPLE_DB_NS(poller)

#endif
