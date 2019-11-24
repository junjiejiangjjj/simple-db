#include "socket_opt.h"
#include <unistd.h>

BEGIN_SIMPLE_DB_NS(net)

SocketOpt::SocketOpt(int fd) : mFd(fd)
{
}
SocketOpt::~SocketOpt()
{
}

int SocketOpt::Read(char *buf, size_t bufSize)
{
    if (mFd < -1) {
        LOG_ERROR << "Can not read fd " << mFd;
        return -1;
    }

    return read(mFd, buf, bufSize);
}

int SocketOpt::Write(const char *data, size_t length)
{
    if (mFd < -1) {
        LOG_ERROR << "Can not write fd " << mFd;
        return -1;
    }

    return write(mFd, data, length);
}

END_SIMPLE_DB_NS(net)

