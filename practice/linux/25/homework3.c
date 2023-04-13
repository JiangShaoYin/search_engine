#include <func.h>

int main(int argc, const char* argv[]){
    if(fork() == 0){
        exit(-1);
    }
    int val;
    wait(&val);
    printf("%d\n",WEXITSTATUS(val));
    return 0;
}

