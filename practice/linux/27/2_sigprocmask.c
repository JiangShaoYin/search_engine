#include <func.h>

void handler(int signum){
    printf("this is handler, signum = %d\n",signum);
}
int main(int argc, const char* argv[]){
    signal(2, handler);
    sigset_t oldset;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, 2);
    sigprocmask(SIG_BLOCK,&newset,&oldset);
    sleep(5);
    sigset_t pendingset;
    sigpending(&pendingset);
    if(sigismember(&pendingset,SIGINT)){
        printf("the pending signal is SIGINT\n");
    }
    sigprocmask(SIG_SETMASK,&oldset,NULL);
    while(1);
    return 0;
}

