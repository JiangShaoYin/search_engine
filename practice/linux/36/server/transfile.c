#include "head.h"

int transferfile(int netfd){
    int fd = open("file1", O_RDWR);
    Train_t train = {5, "file1"};
    int ret = send(netfd, &train, sizeof(int) + train.length, 0);
    ERROR_CHECK(ret, -1, "send");
    // 文件长度发过去
    struct stat statbuf;
    fstat(fd,&statbuf);
    train.length = sizeof(statbuf.st_size);
    bzero(train.buf, sizeof(train.buf));
    memcpy(train.buf, &statbuf.st_size, train.length);
    ret = send(netfd, &train, sizeof(int) + train.length, MSG_NOSIGNAL);
    while(1){
        bzero(&train, sizeof(train));
        int rdret = read(fd, train.buf, sizeof(train.buf));
        train.length = rdret;
        ret = send(netfd, &train, sizeof(int) + train.length, MSG_NOSIGNAL);
        ERROR_CHECK(ret, -1, "send");
        if(rdret == 0){
            break;
        }
    }
    return 0;
}
