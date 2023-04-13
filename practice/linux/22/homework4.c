#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);

    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    char *buf = (char*)mmap(NULL,507,O_RDWR,MAP_SHARED,fd,0);
    for(int i = 0; i < 507; i++){
        if(buf[i] >= 97 && buf[i] <= 122){
            buf[i] += 'A' - 'a';
        }else if(ispunct(buf[i])){
            buf[i] = ' ';
        }
    }
    munmap(buf,507);
    close(fd);
    return 0;
}

