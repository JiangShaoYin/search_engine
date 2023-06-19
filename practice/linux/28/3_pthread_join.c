#include <func.h>

void *thread_func1(void *args) {
    sleep(1);
    pthread_exit((void *) 111);
}
void *thread_func2(void *args) {
    sleep(1);
    pthread_exit((void *) 222);
}
void *thread_func3(void *args) {
    sleep(1);
    pthread_exit((void *) 333);
}
int main(int argc, const char* argv[]){
    pthread_t pth1;
    int ret = pthread_create(&pth1,NULL,thread_func1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create1");
    pthread_t pth2;
    ret = pthread_create(&pth2,NULL,thread_func2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create2");
    pthread_t pth3;
    ret = pthread_create(&pth3,NULL,thread_func3,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create3");
    void * l1;
    pthread_join(pth1,&l1);
    printf("l1 = %ld\n",(long)l1);
    void * l2;
    pthread_join(pth2,&l2);
    printf("l2 = %ld\n",(long)l2);
    void * l3;
    pthread_join(pth3,&l3);
    printf("l3 = %ld\n",(long)l3);
    return 0;
}

