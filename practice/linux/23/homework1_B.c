#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    char buf[256] = {0};
    read(fd,buf,sizeof(buf));
    printf("%s",buf);
    close(fd);
    return 0;
}

