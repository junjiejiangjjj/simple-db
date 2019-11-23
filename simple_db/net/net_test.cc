#include <iostream>
#include <unistd.h>
#include "tcp_server.h"

/*
  创建一个简单的TCP SERVER
  1. 
 */
void Echo(int fd)
{
    char c[1024];
    std::cout << "test" << std::endl;
    read(fd, c, 1024);
    write(fd, "nice", 4);
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
