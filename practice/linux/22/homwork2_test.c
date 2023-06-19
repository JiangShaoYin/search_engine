#include <func.h>
#define N 1000000

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR|O_CREAT, 0666);
    ERROR_CHECK(fd, -1,"open");
    
    ftruncate(fd, N);
    char *buf =(char*) mmap(NULL,N,O_RDWR,MAP_SHARED,fd,0);
    memset(buf,'1',N);
    munmap(buf, N);
    close(fd);
    return 0;
}

