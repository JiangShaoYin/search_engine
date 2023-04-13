#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 3);

    int fd1 = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd1,-1,"open 1");
    int fd2 = open(argv[2],O_RDONLY);
    ERROR_CHECK(fd2, -1, "open 2");

    char buf1[1024];
    char buf2[1024];
    while(1){
        memset(buf1,0,sizeof(buf1));
        memset(buf2,0,sizeof(buf2));
        int ret1 = read(fd1,buf1 , sizeof(buf1) - 1);
        if(ret1 == 0){
            break;
        }

        int ret2 = read(fd2, buf2, sizeof(buf2) - 1);
        if(ret2 == 0){
            break;
        }

        if(strcmp(buf1, buf2) != 0){
            printf("not same\n");
            return 0;
        }
    }

    if(strcmp(buf1, buf2) == 0){
        printf("same\n");
    }else{
        printf("not same\n");
    }
    return 0;
}

