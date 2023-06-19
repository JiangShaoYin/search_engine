#include <func.h>

typedef struct ShareRes{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    int flag;// 0 print A, 1 print B, 2 print C
}ShareRes;

void *funct1(void *arg){
    ShareRes *shareres = (ShareRes*) arg;
    while(1){
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->flag != 0){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("A\n");
        sleep(1);
        shareres->flag = 1;
        pthread_cond_signal(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);

        pthread_mutex_lock(&shareres->mutex);
        while(shareres->flag != 2){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("C\n");
        sleep(1);
        shareres->flag = 0;
        pthread_cond_signal(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}

void *funct2(void *arg){
    ShareRes *shareres = (ShareRes*) arg;
    while(1){
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->flag != 1){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("B\n");
        sleep(1);
        shareres->flag = 2;
        pthread_cond_signal(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc, const char* argv[]){
    ShareRes shareres;
    pthread_mutex_init(&shareres.mutex,NULL);
    pthread_cond_init(&shareres.cond,NULL);
    shareres.flag = 0;
    pthread_t pth1, pth2;
    pthread_create(&pth1,NULL,funct1,&shareres);
    pthread_create(&pth2,NULL,funct2,&shareres);
    pthread_join(pth1,NULL);
    pthread_join(pth2,NULL);
    pthread_mutex_destroy(&shareres.mutex);
    pthread_cond_destroy(&shareres.cond);
    return 0;
}

