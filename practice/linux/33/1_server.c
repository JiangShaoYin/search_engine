#include <func.h>
#define N 4096

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
    // 4 accept
    struct sockaddr_in clientadd;
    socklen_t len = sizeof(clientadd);
    int netfd = accept(sockfd,(struct sockaddr *) &clientadd,&len);
    ERROR_CHECK(netfd,-1,"accept");
    printf("client ip = %s, port = %d\n",inet_ntoa(clientadd.sin_addr),ntohs(clientadd.sin_port));
    // 5 select
    fd_set rdset;
    char buf[N]= {0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(netfd, &rdset);
        select(netfd+1, &rdset, NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            int ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){
                break;
            }
            send(netfd,buf,strlen(buf),0);
        }
        if(FD_ISSET(netfd,&rdset)){
            bzero(buf,sizeof(buf));
            int rdret = recv(netfd,buf,sizeof(buf),0);
            if(rdret == 0){
                printf("the client is close\n");
                break;
            }
            printf("buf = %s\n",buf);
        }
    }
    close(netfd);
    close(sockfd);
    return 0;
}

