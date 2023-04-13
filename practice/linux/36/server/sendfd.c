#include "head.h"

int sendfd(int fdtosend, int socketfd) {
    struct msghdr hdr;
    bzero(&hdr, sizeof(hdr)); // 前两个成员
    // 正文
    struct iovec iove[2];
    char buf1[] = "buf1";
    char buf2[] = "buf2";
    iove[0].iov_base = buf1;
    iove[0].iov_len = 4;
    iove[1].iov_base = buf2;
    iove[1].iov_len = 4;
    hdr.msg_iov = iove;
    hdr.msg_iovlen = 2;
    struct cmsghdr *chdr = (struct cmsghdr *) calloc(1, CMSG_LEN(sizeof(int)));
    chdr->cmsg_len = CMSG_LEN(sizeof(int));
    chdr->cmsg_level = SOL_SOCKET;
    chdr->cmsg_type = SCM_RIGHTS;
    *(int*)CMSG_DATA(chdr) = fdtosend;
    hdr.msg_control = (void*) chdr;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = sendmsg(socketfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "send msg");
    return 0;
}

int recvfd(int *fdtorecv, int socketfd){
    struct msghdr hdr;
    bzero(&hdr, sizeof(hdr)); // 前两个成员
    // 正文
    struct iovec iove[2];
    char buf1[] = "buf1";
    char buf2[] = "buf2";
    iove[0].iov_base = buf1;
    iove[0].iov_len = 4;
    iove[1].iov_base = buf2;
    iove[1].iov_len = 4;
    hdr.msg_iov = iove;
    hdr.msg_iovlen = 2;
    struct cmsghdr *chdr = (struct cmsghdr *) calloc(1, CMSG_LEN(sizeof(int)));
    chdr->cmsg_len = CMSG_LEN(sizeof(int));
    chdr->cmsg_level = SOL_SOCKET;
    chdr->cmsg_type = SCM_RIGHTS;
    hdr.msg_control = (void*) chdr;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = recvmsg(socketfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "recv msg");
    *fdtorecv = *(int*)CMSG_DATA(chdr);
    return 0;
}

