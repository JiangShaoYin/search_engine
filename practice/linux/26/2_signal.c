#include <func.h>

void sig_handler(int signum){
    printf("start sleep sig = %d\n",signum);
    sleep(5);
    printf("end sleep sig = %d\n",signum);
}
int main(int argc, const char* argv[]){
    signal(2, sig_handler);
    signal(3, sig_handler);
    while(1);
    return 0;
}

