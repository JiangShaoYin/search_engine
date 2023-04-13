#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 2);

    int fd = open(argv[1],O_WRONLY);
    ERROR_CHECK(fd,-1,"open");
    dup2(STDOUT_FILENO,4);
    printf("1- Helloworld\n");
    dup2(fd,STDOUT_FILENO);
    printf("2- Helloworld\n");
    dup2(4,STDOUT_FILENO);
    printf("3- Helloworld\n");
    close(fd);
    close(4);
    return 0;
}

