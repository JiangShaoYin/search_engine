#include <func.h>

void deamon_func(){
    chdir("/");
    setsid();
    for(int i = 0;i<3;i++){
        close(i);
    }
    umask(0);
    for(int i = 0; i < 30; i++){
        sleep(2);
        time_t now = time(NULL);
        syslog(LOG_INFO,"DEAMOND %s\n", ctime(&now));
    }
}

int main(int argc, const char* argv[]){
    if(fork() == 0){
        deamon_func();
    }
    return 0;
}

