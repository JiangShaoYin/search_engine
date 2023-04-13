#include <func.h>
#define N 100
int main(int argc, const char* argv[]){
    // ./1_epollTCP 0.0.0.0 1234
    ARGC_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sockfd, -1, "socket");
    struct sockaddr_in soaddr;
    soaddr.sin_family = AF_INET;
    soaddr.sin_port = htons(atoi(argv[2]));
    soaddr.sin_addr.s_addr = inet_addr(argv[1]);
    int bindres = bind(sockfd, (struct sockaddr *)&soaddr, sizeof(soaddr));
    ERROR_CHECK(bindres, -1, "bind");

    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    char buf[4096] = {0};
    recvfrom(sockfd, (void *)buf, sizeof(buf),0, (struct sockaddr*)&clientaddr, &len);
    printf("client ip = %s, port = %d\n", 
           inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
    printf("buf = %s\n", buf);
    fd_set rdset;
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(sockfd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);
        select(sockfd + 1, &rdset, NULL, NULL, NULL);
        if( FD_ISSET(sockfd, &rdset)) {
            bzero(buf, sizeof(buf));
            int rdret = recvfrom(sockfd, (void *)buf, sizeof(buf),0, NULL, NULL);
            if(rdret == 0){
                printf("the client is close, i will close soon\n");
                break;
            }
            printf("buf = %s\n", buf);
        }
        if( FD_ISSET(STDIN_FILENO, &rdset)) {
            bzero(buf, sizeof(buf));
            int rdres = read( STDIN_FILENO, buf, sizeof(buf));
            if(rdres == 0){
                printf("this server will close soon\n");
                sendto(sockfd, buf, 0, 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
                break;
            }
            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &clientaddr, sizeof(clientaddr));
        }
    }
    close(sockfd);
    return 0;
}

