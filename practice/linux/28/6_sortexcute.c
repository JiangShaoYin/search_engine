#include <func.h>

int if_excute_B = 0;
void *thread_func(void* args){
    pthread_mutex_t *mutex = (pthread_mutex_t*) args;
    pthread_mutex_lock(mutex);
    printf("Doing task A\n");
    sleep(3);
    printf("Finish doing task A\n");
    if_excute_B = 1;
    pthread_mutex_unlock(mutex);
    pthread_exit((void*)1);
}
void *thread_fun2(void* args){
    pthread_mutex_t *mutex = (pthread_mutex_t*) args;
    while(1){
        if(if_excute_B){
            pthread_mutex_lock(mutex);
            printf("Doing task B\n");
            pthread_mutex_unlock(mutex);
            pthread_exit((void*)123);
        }
    }
}
int main(int argc, const char* argv[]){
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    pthread_t pth1;
    int ret1 = pthread_create(&pth1,NULL,thread_func,(void *)&mutex);
    THREAD_ERROR_CHECK(ret1,"pthread_create1");
    pthread_t pth2;
    int ret2 = pthread_create(&pth2,NULL,thread_fun2,(void*)&mutex);
    THREAD_ERROR_CHECK(ret2,"pthread_create2");
    pthread_join(pth1,NULL);
    pthread_join(pth2,NULL);
    return 0;
}

