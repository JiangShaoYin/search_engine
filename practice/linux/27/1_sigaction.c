#include <func.h>

void handler(int signum, siginfo_t *info, void *p){
    printf("before signum = %d, pid = %d\n",signum,info->si_pid);
    sleep(5);
    printf("after signum = %d\n",signum);
}
int main(int argc, const char* argv[]){
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_flags = SA_RESTART|SA_SIGINFO;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    sigaction(2,&act,NULL);
    while(1);
    return 0;
}

