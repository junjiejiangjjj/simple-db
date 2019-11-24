#ifndef SIMPLE_DB_SOCKET_OPT_H
#define SIMPLE_DB_SOCKET_OPT_H

#include "simple_db/common/common.h" 

BEGIN_SIMPLE_DB_NS(net)

class SocketOpt {
public:
    explicit SocketOpt(int fd);
    virtual ~SocketOpt();
private:
    SocketOpt(const SocketOpt&);
    SocketOpt& operator=(const SocketOpt&);

public:
    int Read(char *buf, size_t bufSize);
    int Write(const char *data, size_t length);

private:
    int mFd;
};

END_SIMPLE_DB_NS(net)

#endif
