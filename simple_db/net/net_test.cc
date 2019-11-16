#include <iostream>
#include "tcp_server.h"

/*
  创建一个简单的TCP SERVER
  1. 
 */


int main()
{
    simple_db::net::TCPServer server;
    server.Bind(10000);
    server.Start();
    return 0;
}
