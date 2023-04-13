#include "head.h"

int tcpInit(const char* ip, const char* port, int *socketfd) {
    *socketfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    int ret = setsockopt(*socketfd, SOL_SOCKET,SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, -1, "set socket option");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    ret = bind(*socketfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "bind");
    ret = listen(*socketfd, 10);
    return 0;
}

