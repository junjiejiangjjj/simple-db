#ifndef SIMPLE_DB_EVENT_H
#define SIMPLE_DB_EVENT_H

BEGIN_SIMPLE_DB_NS(net)

class Event {
    // epoll中的事件

private:
    static const int EPOLLIN = 0x001;
    static const int EPOLLPRI = 0x002;
    static const int EPOLLOUT = 0x004;
    static const int EPOLLERR = 0x008;
    static const int EPOLLHUP = 0x010;
    static const int EPOLLRDHUP = 0x2000;
    static const int EPOLLONESHOT = (1 << 30);
    static const int EPOLLET = (1 << 31);

public:
    static const int NoneEvent = 0;
    static const int ReadEvent = EPOLLIN;
    static const int WriteEvent = EPOLLOUT;
    static const int ErrorEvent = EPOLLERR | EPOLLHUP;
};

END_SIMPLE_DB_NS(net)

#endif
