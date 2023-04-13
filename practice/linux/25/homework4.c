#include <func.h>

int main(int argc, const char* argv[]){
    int fds[2];
    pipe(fds);
    if(fork() == 0){
        close(fds[0]);
        //char buf[4096];
        //sleep(5);
        //printf("start write\n");
        //int res =  write(fds[1],buf,sizeof(buf));
        //printf("res = %d\n",res);
        close(fds[1]);
    }else{
        close(fds[1]);
        char buf[256];
        //sleep(10);
        //read(fds[0],buf,sizeof(buf));
        //printf("%s", buf);
        //while(1);
        //close(fds[0]);
        //while(1);
        sleep(5);
        printf("start read\n");
        int res = read(fds[0],buf, sizeof(buf));
        printf("read end\n");
        printf("res = %d\n", res);
    }
    return 0;
}

