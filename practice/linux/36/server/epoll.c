#include "head.h"

int epollAdd(int epfd, int socketfd){
    struct epoll_event event;
    event.data.fd = socketfd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD, socketfd, &event);
    ERROR_CHECK(ret, -1, "epoll add");
    return 0;
}
int epollDel(int epfd, int socketfd){
    struct epoll_event event;
    int ret = epoll_ctl(epfd,EPOLL_CTL_DEL, socketfd, NULL);
    ERROR_CHECK(ret, -1, "epoll del");
    return 0;
}
