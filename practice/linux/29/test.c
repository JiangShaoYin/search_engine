#include <func.h>
typedef struct node{
    int data;
    struct node *next;
} Node;
Node* init(){
    Node *head = (Node*) malloc(sizeof(Node));
    head->next = NULL;
    return head;
}
void push(Node *head, int data){
    Node *p = (Node*) malloc(sizeof(Node));
    p->data = data;
    p->next = head->next;
    head->next = p;
}
int pop(Node *head){
    Node *p = head->next;
    if(p == NULL){
        printf("queue is empty\n");
        return -1;
    }
    head->next = p->next;
    int data = p->data;
    free(p);
    return data;
}
int main(){
    // using linked list make a FIFO queue to store int data
    // this queue provides two functions: push and pop
    // push: push a new node to the head of the queue
    // pop: pop the tail node of the queue

    Node *head = init();
    push(head, 1);
    push(head, 2);
    push(head, 3);
}