#include <unistd.h>
#include <fcntl.h>
#include "simple_db/net/net_util.h"
#include <string.h>


BEGIN_SIMPLE_DB_NS(net)


/* static */ int NetUtil::Bind(int port)
{
    struct sockaddr_in seraddr;
    bzero(&seraddr, sizeof(seraddr));
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);
    int opt = SO_REUSEADDR;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        LOG_ERROR << "Set socket reuse failed";
        return -1;
    }
    if (bind(fd, (sockaddr *)&seraddr, sizeof(seraddr)) != 0) {
        LOG_ERROR << "Do bind failed, error code " << errno;
        return -1;
    }
    if (listen(fd, 128) != 0) {
        LOG_ERROR << "Do listen failed";
        return -1;
    }
    SetNoBlock(fd);
    return fd;    
}

/* static */ int NetUtil::Accept(int fd, sockaddr_in *addr, socklen_t *addrlen)
{
    return accept(fd, (sockaddr*)addr, addrlen);    
}

/* static */ void NetUtil::SetNoBlock(int fd)
{
    int option = fcntl(fd, F_GETFL, 0);
    option |= O_NONBLOCK;
    fcntl(fd, F_SETFL, option);    
}

END_SIMPLE_DB_NS(net)

