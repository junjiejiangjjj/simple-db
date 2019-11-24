#ifndef SIMPLE_DB_ACCEPTOR_H
#define SIMPLE_DB_ACCEPTOR_H

#include "simple_db/common/common.h"
#include <sys/socket.h>
#include <netinet/in.h>

BEGIN_SIMPLE_DB_NS(net)

class NetUtil {
private:
    NetUtil();
    ~NetUtil();
private:
    NetUtil(const NetUtil&);
    NetUtil& operator=(const NetUtil&);

public:
    static int Bind(int port);
    static int Accept(int fd, struct sockaddr_in *addr,socklen_t *addrlen);
    static void SetNoBlock(int fd);
};

END_SIMPLE_DB_NS(net)

#endif
