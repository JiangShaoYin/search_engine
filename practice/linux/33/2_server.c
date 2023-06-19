#include <func.h>
#define N 4096
#define M 1024

int main(int argc, const char* argv[]){
    //./1_server 192.168.90.19 1234
    ARGC_CHECK(argc,3);
    // 1 socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // 2 bind
    struct sockaddr_in soaddr;
    soaddr.sin_family = AF_INET;
    soaddr.sin_port = htons(atoi(argv[2]));
    soaddr.sin_addr.s_addr = inet_addr(argv[1]);
    int bindret = bind(sockfd,(struct sockaddr *)&soaddr,sizeof(soaddr));
    ERROR_CHECK(bindret, -1, "bind");
    // 3 listen
    int listenret = listen(sockfd, 10);
    ERROR_CHECK(listenret,-1,"listen");
    // 5 select
    fd_set monitorset;
    FD_ZERO(&monitorset);
    FD_SET(sockfd, &monitorset);
    FD_SET(STDIN_FILENO, &monitorset);
    fd_set rdset;
    char buf[N]= {0};
    int map[M + 1] = {0};
    while(1){
        FD_ZERO(&rdset);
        memcpy(&rdset,&monitorset,sizeof(rdset));
        select(10, &rdset, NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            struct sockaddr_in clientadd;
            socklen_t len = sizeof(clientadd);
            int netfd = accept(sockfd,(struct sockaddr *) &clientadd,&len);
            ERROR_CHECK(netfd,-1,"accept");
            printf("client ip = %s, port = %d\n",inet_ntoa(clientadd.sin_addr),ntohs(clientadd.sin_port));
            FD_SET(netfd, &monitorset);
            map[netfd] = 1;
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            int ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){
                break;
            }
            for(int i = 0; i < M; ++i) {
                if(map[i] == 0) continue;
                send(i, buf, strlen(buf), 0);
            }
        }
        for(int i = 0; i <= M; i++) {
            if(map[i] == 0) continue;
            if(FD_ISSET(i,&rdset)){
                bzero(buf,sizeof(buf));
                int rdret = recv(i,buf,sizeof(buf),0);
                if(rdret == 0){
                    printf("the client is close\n");
                    close(i);
                    map[i] = 0;
                    FD_CLR(i,&monitorset);
                }
                printf("buf = %s\n",buf);
            }
        }
    }
    for(int i = 0; i < M; ++i) {
        if(map[i] == 0) continue;
        close(i);
    }
    close(sockfd);
    return 0;
}

