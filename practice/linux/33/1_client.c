#include <func.h>
#define N 4096

int main(int argc, const char* argv[]){
    //./1_server 192.168.90.19 1234
    ARGC_CHECK(argc,3);
    // 1 socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // 2 connect
    struct sockaddr_in soaddr;
    soaddr.sin_family = AF_INET;
    soaddr.sin_port = htons(atoi(argv[2]));
    soaddr.sin_addr.s_addr = inet_addr(argv[1]);
    int connectret = connect(sockfd,(struct sockaddr *)&soaddr,sizeof(soaddr));
    ERROR_CHECK(connectret, -1, "connet");
    fd_set rdset;
    char buf[N] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);
        select(sockfd+1, &rdset, NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            int ret = read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){
                break;
            }
            send(sockfd,buf,strlen(buf),0);
        }
        if(FD_ISSET(sockfd,&rdset)){
            bzero(buf,sizeof(buf));
            int rdret = recv(sockfd,buf,sizeof(buf),0);
            if(rdret == 0){
                printf("the server is close\n");
                break;
            }
            printf("buf = %s\n",buf);
        }
    }
    return 0;
}

