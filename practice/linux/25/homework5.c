#include <func.h>

int main(int argc, const char* argv[]){
    if(fork()==0){
       system("./homework5_in .");
    }else{
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("Nomal exit, WIFEXITED(wstatus) = %d\n",WIFEXITED(wstatus));
        }else if(WIFSIGNALED(wstatus)){
            printf("Signal exit, WIFSIGNALED(wstatus) = %d\n",WIFSIGNALED(wstatus));
        }
    }
    return 0;
}

