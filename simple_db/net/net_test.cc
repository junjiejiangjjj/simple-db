#include <iostream>
#include <unistd.h>
#include "tcp_server.h"
#include "simple_db/net/socket_opt.h"

/*
  创建一个简单的TCP SERVER
  1. 
 */

void Echo(simple_db::net::SocketOpt *sckOpt)
{
    char c[1024] = {0};
    sckOpt->Read(c, 1024);
    std::cout << c << std::endl;
    sckOpt->Write("nice", 4);
}

int main()
{
    simple_db::net::TCPServer server;
    if (!server.Bind(10000)) {
        return -1;
    }
    server.SetOnMessage(std::bind(Echo, std::placeholders::_1));
    server.Start();
    return 0;
}
