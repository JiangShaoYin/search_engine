#include <func.h>

void handler(int signum){
    printf("the sig is %d\n", signum);
    time_t now = time(NULL);
    printf("now is %s\n",ctime(&now));
}
int main(int argc, const char* argv[]){
    time_t now = time(NULL);
    printf("now is %s\n",ctime(&now));
    struct itimerval timer;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    signal(SIGPROF,handler);
    signal(SIGALRM,handler);
    setitimer(ITIMER_PROF,&timer,NULL);
    setitimer(ITIMER_REAL,&timer,NULL);
    while(1);
    return 0;
}

