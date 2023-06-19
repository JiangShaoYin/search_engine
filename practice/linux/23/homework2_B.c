#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,3);

    int fdw = open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open fdw");
    int fdr = open(argv[2],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open fdw");

    fd_set fset;
    char buf[4096];
    while(1){
        FD_ZERO(&fset);
        FD_SET(STDIN_FILENO, &fset);
        FD_SET(fdr, &fset);

        int res = select(fdr+1, &fset, NULL, NULL, NULL);
        if(FD_ISSET(fdr,&fset)){
            memset(buf,0,sizeof(buf));
            int ret_cnt =  read(fdr,buf,sizeof(buf));
            if(ret_cnt == 0){
                printf("close pipe\n");
                return 0;
            }
            printf("buf = %s\n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&fset)){
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            write(fdw,buf,strlen(buf));
        }


    }
    return 0;
}

