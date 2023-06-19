#include "head.h"

int main(int argc, const char* argv[]){
    // ./mian 0.0.0.0 1234 3
    ARGC_CHECK(argc, 4);
    int workernum = atoi(argv[3]);
    WorkerData_t * workerData = (WorkerData_t *) calloc(workernum, sizeof(WorkerData_t));
    int ret = createWorkers(workernum, workerData);
    ERROR_CHECK(ret, -1, "create workers");
    int socketfd;
    ret = tcpInit(argv[1], argv[2], &socketfd);
    ERROR_CHECK(ret, -1, "tcp init");
    int epfd = epoll_create(10);
    epollAdd(epfd, socketfd);
    for(int i = 0; i < workernum; ++i) {
        epollAdd(epfd, workerData[i].socketfd);    
    }
    while(1){
        struct epoll_event *clientEvent = (struct epoll_event *) calloc(1 + workernum, sizeof(struct epoll_event));
        int readynum = epoll_wait(epfd, clientEvent, 1 + workernum, -1);
        for(int i = 0; i < readynum; ++i){
            if(socketfd == clientEvent[i].data.fd) {
                struct sockaddr_in clientadd;
                socklen_t len = sizeof(clientadd);
                int netfd = accept(socketfd, (struct sockaddr *)&clientadd, &len);
                //printf("client ip = %s, port = %d\n", inet_ntoa(clientadd.sin_addr), ntohs(clientadd.sin_port));
                printf("new link comming: ip = %s, port = %d\n",inet_ntoa(clientadd.sin_addr), ntohs(clientadd.sin_port));
                for(int j = 0; j < workernum; ++j){
                    if(workerData[j].status == FREE){
                        printf("child process %d begin work, pid is %d, client ip = = %s, port = %d\n", j, workerData[j].pid, inet_ntoa(clientadd.sin_addr), ntohs(clientadd.sin_port));
                        sendfd(netfd, workerData[j].socketfd);
                        workerData[j].status = BUSY;
                        break;
                    }
                }
                close(netfd);
            }else{
                for(int j = 0; j < workernum; ++j) {
                    if(workerData[j].socketfd == clientEvent[i].data.fd) {
                        int pid;
                        int ret = recv(workerData[j].socketfd, &pid, sizeof(int), 0);
                        ERROR_CHECK(ret, -1, "recv from child");
                        printf("child %d finish work\n", pid);
                        workerData[j].status = FREE;
                    }
                }
            }
        }
    }
    return 0;
}

