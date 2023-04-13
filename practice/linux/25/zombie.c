#include <func.h>

int main(int argc, const char* argv[]){
    printf("begin zombie.\n");
    if(fork() == 0){
        printf("The son gonna to die\n");
        return 0;
    }
    printf("Father starts loop\n");
    while(1);
    return 0;
}

