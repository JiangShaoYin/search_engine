#include "head.h"

int createWorkers(int workernum, WorkerData_t *workerData){
    for(int i = 0; i < workernum; ++i){
        int fds[2];
        int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);
        int pid = fork();
        if(pid == 0){
            close(fds[0]);
            eventloop(fds[1]);
        }
        workerData[i].status = FREE;
        workerData[i].pid = pid;
        workerData[i].socketfd = fds[0];
        close(fds[1]);
        printf("create worker %d, pid = %d, socketfd = %d\n", i, pid, fds[0]);
    }
    return 0;
}

void eventloop(int socketfd) {
    while(1){
        int netfd;
        int ret = recvfd(&netfd, socketfd);
        ERROR_CHECK(ret, -1, "recvfd");
        ret = transferfile(netfd);
        ERROR_CHECK(ret, -1, "transfer file");
        int pid = getpid();
        send(socketfd, &pid, sizeof(int), 0);
    }
}

