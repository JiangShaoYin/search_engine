#include <func.h>

int recvn(int socketfd, void *buf, int len) {
    int total = 0;
    char *p = (char*) buf;
    while(total < len){
        int ret = recv(socketfd, p + total, len - total, 0);
        total += ret;
    }
    return total;
}

int recvfile(int socketfd) {
    int namelen;
    char filename[1024] = {0};
    recvn(socketfd, &namelen, sizeof(int));
    recvn(socketfd, filename, namelen);
    // 收取文件长度
    int len;
    int filelen;
    recvn(socketfd, &len, sizeof(int));
    recvn(socketfd, &filelen, len);
    printf("the file length is %d\n",filelen);
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    int split = filelen / 10000;
    int lastlen = 0;
    int curlen = 0;
    while(1){
        int length;
        int buf[1024] = {0};
        recvn(socketfd, &length, sizeof(int));
        if(length == 0){
            break;
        }
        recvn(socketfd, buf, length);
        int ret = write(fd, buf, length);
        ERROR_CHECK(ret, -1, "write");
        curlen += length;
        if(curlen - lastlen > split){
            printf("%5.2lf%%\r", 100.0 * curlen / filelen);
            lastlen = curlen;
        }
    }
    printf("100.0%%\n");
    return 0;
}
int main(int argc, const char* argv[]){
    // ./client 0.0.0.0 1234
    ARGC_CHECK(argc, 3);
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    ERROR_CHECK(ret, -1, "connect");
    //char buf[1024] = {0};
    //recv(socketfd, buf, sizeof(buf), 0);
    //printf("buf = %s\n", buf);
    ret = recvfile(socketfd);
    ERROR_CHECK(ret, -1, "recv file");

    return 0;
}

