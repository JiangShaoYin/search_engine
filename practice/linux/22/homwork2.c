#include <func.h>
#define N 10000
int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR|O_APPEND|O_CREAT, 0666);
    char *buf =(char*) malloc(N);
    memset(buf,'1',N);
    
    int cnt = 100;
    while(cnt > 0){
        int ret = write(fd,buf, N);
        ERROR_CHECK(ret, -1, "write");
        cnt--;
    }

    return 0;
}

