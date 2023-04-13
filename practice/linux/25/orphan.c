#include <func.h>

int main(int argc, const char* argv[]){
    printf("orphan start\n");
    if(fork() == 0){
        printf("this is son, i will sleep 10 sec\n");
        sleep(10);
    }
    return 0;
}

