#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,3);

    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open fdr");
    int fdw = open(argv[2],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open fdw");

    fd_set fset;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    char buf[4096];
    time_t cur_time = time(NULL);
    while(1){
        FD_ZERO(&fset);
        FD_SET(STDIN_FILENO,&fset);
        FD_SET(fdr,&fset);

        int res =  select(fdw+1,&fset,NULL,NULL,&tv);
        ERROR_CHECK(res,-1,"select");
        
        time_t now = time(NULL);
        if(now - cur_time > 10){
            printf("pipe timeout\n");
            return 0;
        }

        if(FD_ISSET(fdr,&fset)){
            cur_time = now;
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

