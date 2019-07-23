#ifndef SIMPLE_DB_LOGG_STREAM_H
#define SIMPLE_DB_LOGG_STREAM_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(util)

class LoggStream {
public:
    LoggStream();
    ~LoggStream();
private:
    LoggStream(const LoggStream&);
    LoggStream& operator=(const LoggStream&);
};

END_SIMPLE_DB_NS(util)

#endif