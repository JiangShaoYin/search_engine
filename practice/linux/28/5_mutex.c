#include <func.h>
#define N 20000000
int num = 0;
void *thread_func(void *args){
    pthread_mutex_t *mutex = (pthread_mutex_t*) args;
    for(int i = 0; i < N; i++){
        pthread_mutex_lock(mutex);
        num++;
        pthread_mutex_unlock(mutex);
    }
    pthread_exit((void*)1);
}
int main(int argc, const char* argv[]){
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    pthread_t pth;
    struct timeval start,end;
    gettimeofday(&start,NULL);
    int ret = pthread_create(&pth,NULL,thread_func,(void*) &mutex);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(int i  = 0; i < N; i++){
        pthread_mutex_lock(&mutex);
        num++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(pth,NULL);
    gettimeofday(&end,NULL);
    printf("num = %d, sec_gap = %ld, usec_gap = %ld\n", num,end.tv_sec - start.tv_sec ,end.tv_usec - start.tv_usec);
    return 0;
}

