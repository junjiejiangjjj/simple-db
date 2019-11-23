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
    if (bind(fd, (sockaddr *)&seraddr, sizeof(seraddr)) != 0) {
        LOG_ERROR << "Do bind failed, error code " << errno;
        return -1;
    }
    if (listen(fd, 128) != 0) {
        LOG_ERROR << "Do listen failed";
        return -1;
    }
    int option = fcntl(fd, F_GETFL, 0);
    option |= O_NONBLOCK;
    fcntl(fd, F_SETFL, option);
    
    return fd;    
}

/* static */ int NetUtil::Accept(int fd, sockaddr_in *addr, socklen_t *addrlen)
{
    return accept(fd, (sockaddr*)addr, addrlen);    
}

END_SIMPLE_DB_NS(net)

