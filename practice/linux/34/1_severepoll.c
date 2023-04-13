#include <func.h>
#define N 100
int main(int argc, const char* argv[]){
    // ./1_epollTCP 0.0.0.0 1234
    ARGC_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in soaddr;
    soaddr.sin_family = AF_INET;
    soaddr.sin_port = htons(atoi(argv[2]));
    soaddr.sin_addr.s_addr = inet_addr(argv[1]);
    int bindres = bind(sockfd,(struct sockaddr *)&soaddr,sizeof(soaddr));
    ERROR_CHECK(bindres, -1, "bind");
    int lires = listen(sockfd, 1);
    ERROR_CHECK(lires, -1, "listen");

    int epfd = epoll_create(1);
    ERROR_CHECK(epfd, -1, "epoll_create");
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    int ctl_res = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd,&event);
    ERROR_CHECK(ctl_res, -1, "epoll_ctl");
    int netfd;
    char buf[4096] = {0};
    while(1) {
        struct epoll_event readyevent[N];
        int ret = epoll_wait(epfd, readyevent, N, -1);
        for(int i = 0; i < ret; ++i) {
            if(readyevent[i].data.fd == sockfd){
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                netfd = accept(sockfd, (struct sockaddr *)&client, &len);
                printf("client ip = %s, port = %d\n", 
                       inet_ntoa(client.sin_addr),
                        ntohs(client.sin_port));
                event.data.fd = netfd;
                ctl_res = epoll_ctl(epfd, EPOLL_CTL_ADD, netfd, &event);
                ERROR_CHECK(ctl_res, -1, "epoll_ctl");
                event.data.fd = STDIN_FILENO;
                ctl_res = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
                ERROR_CHECK(ctl_res, -1, "epoll_ctl");
                event.data.fd = sockfd;
                ctl_res = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd,&event);
                ERROR_CHECK(ctl_res, -1, "epoll_ctl");
            }else if(readyevent[i].data.fd == netfd){
                bzero(buf, sizeof(buf));
                int rdret = recv(netfd, buf, sizeof(buf), 0);
                if(rdret == 0){
                    printf("the client is close, i will wait\n");
                    event.data.fd = netfd;
                    ctl_res = epoll_ctl(epfd, EPOLL_CTL_DEL, netfd, &event);
                    ERROR_CHECK(ctl_res, -1, "epoll_ctl");
                    event.data.fd = STDIN_FILENO;
                    ctl_res = epoll_ctl(epfd, EPOLL_CTL_DEL, STDIN_FILENO, &event);
                    ERROR_CHECK(ctl_res, -1, "epoll_ctl");
                    event.data.fd = sockfd;
                    ctl_res = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd,&event);
                    ERROR_CHECK(ctl_res, -1, "epoll_ctl");
                    close(netfd); 
                    continue;
                }
                printf("buf = %s\n", buf);
            }else if(readyevent[i].data.fd == STDIN_FILENO) {
                bzero(buf, sizeof(buf));
                int rdres = read(STDIN_FILENO, buf, sizeof(buf));
                if(rdres == 0) {
                    printf("this server will close soon\n");
                    goto end;
                }
                send(netfd, buf, strlen(buf), 0);
            }
        }
    }
end:
    close(sockfd);
    close(netfd);
    return 0;
}

