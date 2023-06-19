#include <func.h>

int main(int argc, const char* argv[]){
    int shmid = shmget(0x1234,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p = (char*)shmat(shmid,NULL, 0);
    ERROR_CHECK(p, (void*) -1,"shmat");
    if(fork() == 0){
        sleep(2);
        printf("%s",p);
    }else{
        char c[] = "How are you.";
        for(int i = 0; i < 12; i++){
            p[i] = c[i];
        }
    }
    shmdt(p);
    wait(NULL);
    return 0;
}

