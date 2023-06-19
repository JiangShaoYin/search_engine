#include <func.h>
#include "queue.h"

Queue* create_queue() {
  return (Queue*)calloc(1, sizeof(Queue));
}

void destroy_queue(Queue* q) {
  Node* cur = q->front;
  while (cur) {
    Node* next = cur->next;
    free(cur);
    cur = next;
  }
  free(q);
}

// rear in front out
void push_queue(Queue* q, int val) {
  Node* new_node =(Node*) calloc(1, sizeof(Node));
  new_node->val = val;
  if (q->size == 0) {
    q->front = new_node;
    q->rear = new_node;
  } else {
    q->rear->next = new_node;
    q->rear = new_node;
  }
  q->size++;
}

int pop_queue(Queue* q) {
  if (is_empty(q)) {
    printf("Error: the queue is empty\n");
    exit(1);
  }
  int res = q->front->val;
  Node* tmp = q->front;
  q->front = q->front->next;
  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(tmp);
  q->size--;
  return res;
}

int peek_queue(Queue* q) {
  if (is_empty(q)) {
    printf("Error: the queue is empty\n");
    exit(1);
  }
  return q->front->val;
}

bool is_empty(Queue* q) {
  return q->size == 0;
}

typedef struct ShareRes_s{
    Queue* product;
    int flag; // flag = 1, product is available; flag = 0, product is unavailable
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ShareRes;

void* producefunc1(void* arg){
    ShareRes *shareres = (ShareRes*) arg;
    while(1){
        sleep(3);
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->count == 10){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("before producefunc1, product count = %d\n", shareres->count);
        shareres->count++;
        int res =  rand()%100;
        push_queue(shareres->product, res);
        //sleep(3);
        printf("after producefunc1, product count = %d, product = %d\n", shareres->count, res);
        //pthread_cond_signal(&shareres->cond);
        pthread_cond_broadcast(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
void* producefunc2(void* arg){
    ShareRes *shareres = (ShareRes*) arg;
    while(1){
        sleep(3);
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->count == 10){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("before producefunc2, product count = %d\n", shareres->count);
        shareres->count++;
        int res =  rand()%100;
        push_queue(shareres->product, res);
        //sleep(3);
        printf("after producefunc2, product count = %d, product = %d\n", shareres->count, res);
        //pthread_cond_signal(&shareres->cond);
        pthread_cond_broadcast(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
void* producefunc3(void* arg){
    ShareRes *shareres = (ShareRes*) arg;
    while(1){
        sleep(3);
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->count == 10){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("before producefunc3, product count = %d\n", shareres->count);
        shareres->count++;
        srand(time(NULL));
        int res =  rand()%100;
        push_queue(shareres->product, res);
        //sleep(3);
        printf("after producefunc3, product count = %d, product = %d\n", shareres->count, res);
        //pthread_cond_signal(&shareres->cond);
        pthread_cond_broadcast(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
void* consumefunc1(void* arg){
    ShareRes *shareres = (ShareRes*) arg;
    sleep(5);
    while(1){
        sleep(1);
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->count == 0){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("before consumefunc1, product count = %d\n", shareres->count);
        shareres->count--;
        int res = pop_queue(shareres->product);
        //sleep(1);
        printf("after consumefunc1, product count = %d, product = %d\n", shareres->count, res);
        //pthread_cond_signal(&shareres->cond);
        pthread_cond_broadcast(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
void* consumefunc2(void* arg){
    ShareRes *shareres = (ShareRes*) arg;
    sleep(5);
    while(1){
        sleep(1);
        pthread_mutex_lock(&shareres->mutex);
        while(shareres->count == 0){
            pthread_cond_wait(&shareres->cond, &shareres->mutex);
        }
        printf("before consumefunc2, product count = %d\n", shareres->count);
        shareres->count--;
        int res = pop_queue(shareres->product);
        //sleep(1);
        printf("after consumefunc2, product count = %d, product = %d\n", shareres->count, res);
        //pthread_cond_signal(&shareres->cond);
        pthread_cond_broadcast(&shareres->cond);
        pthread_mutex_unlock(&shareres->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc, const char* argv[]){
    ShareRes shareRes;
    shareRes.product = create_queue();
    // push 8 random numbers into the queue
    srand(time(NULL));
    for (int i = 0; i < 8; i++) {
        int val = rand() % 100;
        push_queue(shareRes.product, val);
        printf("input product %d\n", val);
    }
    shareRes.flag = 1;
    shareRes.count = 8;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond, NULL);
    pthread_t pthid1, pthid2,pthid3,pthid4,pthid5;
    pthread_create(&pthid1, NULL, producefunc1, &shareRes);
    pthread_create(&pthid2, NULL, producefunc2, &shareRes);
    pthread_create(&pthid3, NULL, producefunc3, &shareRes);
    pthread_create(&pthid4, NULL, consumefunc1, &shareRes);
    pthread_create(&pthid5, NULL, consumefunc2, &shareRes);
    pthread_join(pthid1, NULL);
    pthread_join(pthid2, NULL);
    pthread_join(pthid3, NULL);
    pthread_join(pthid4, NULL);
    pthread_join(pthid5, NULL);
    pthread_mutex_destroy(&shareRes.mutex);
    pthread_cond_destroy(&shareRes.cond);
    return 0;
}

