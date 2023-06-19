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

    char buf[4096] = {0};
    fd_set rdset;
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(sockfd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);
        select(sockfd + 10, &rdset, NULL, NULL, NULL);
        if( FD_ISSET(sockfd, &rdset)) {
            bzero(buf, sizeof(buf));
            int rdset = recvfrom(sockfd, (void *)buf, sizeof(buf),0, NULL, NULL);
            if(rdset == 0){
                printf("the server is quit, i quit, too\n");
                break;
            }
            printf("buf = %s\n", buf);
        }
        if( FD_ISSET(STDIN_FILENO, &rdset)) {
            bzero(buf, sizeof(buf));
            int rdres = read( STDIN_FILENO, buf, sizeof(buf));
            if(rdres == 0){
                printf("this client will close soon\n");
                sendto(sockfd, buf, 0, 0, (struct sockaddr *) &soaddr, sizeof(soaddr));
                break;
            }
            sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) &soaddr, sizeof(soaddr));
        }
    }
    close(sockfd);
    return 0;
}

