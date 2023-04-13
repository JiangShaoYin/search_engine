#include <func.h>

int main(int argc, const char* argv[]){
    if(fork() != 0){
        exit(0);
    }
    for(int i = 0; i < 10 ; i++){
        printf("%d\n", i);
        sleep(1);
    }
    return 0;
}

