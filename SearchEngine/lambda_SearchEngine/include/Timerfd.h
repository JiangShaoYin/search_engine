#pragma once

#include <sys/epoll.h>
#include <sys/timerfd.h>
#include "Server_EventLoop.h"
#include <unistd.h>
#include "CacheManager.h"
#include "log4pp.h"

void timerFd()
{
    int _timerfd;
    _timerfd = timerfd_create(CLOCK_REALTIME,0);

    int epfd = epoll_create1(0);
    if (epfd < 0)
    {
        perror("epoll_create1");
    }

    cout << "epfd = " << epfd << endl;
    struct epoll_event evt;
    evt.data.fd = _timerfd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,_timerfd,&evt);
    if (ret < 0)
    {
        perror("epoll_ctl add");
    }

    struct itimerspec value;

    value.it_value.tv_sec = 1;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 3;
    value.it_interval.tv_nsec = 0;

    timerfd_settime(_timerfd, 0, &value, nullptr);

    vector<struct epoll_event> _evtList(2);
    int nready;
    while (1) {
        nready = epoll_wait(epfd,&*_evtList.begin(),_evtList.size(),3000);
        for (int idx = 0; idx < nready;++idx)
        {
            if (_evtList[idx].data.fd == _timerfd)
            {
                uint64_t one = 1;
                read(_timerfd,&one,sizeof(one));
                logInfo("LRU更新缓存");
                CacheManager::GetInstance(nullptr)->updateCache();
            }
        }
    }
}
