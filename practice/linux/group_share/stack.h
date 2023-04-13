#include<func.h>
#define N 8

typedef struct{
  int* element;
  int size;
  int capacity;
} Stack;

Stack *init_stack();
void expand_stack(Stack* stack);
void push_stack(Stack** stack, int val);
int pop_stack(Stack* stack);
int peek_stack(Stack stack);
bool is_empty(Stack stack);

Stack *init_stack(){
    Stack *s = (Stack *)calloc(1,sizeof(Stack));
    s->size = 0;
    s->capacity = N;
    int *el = (int*) calloc(N,sizeof(int));
    s->element = el;
    return s;
}

void expand_stack(Stack* stack) {
  int capacity = stack->capacity * 2;
  int* tmp = (int*)realloc(stack->element, capacity * sizeof(int));
  if (!tmp) {
    printf("Error in expanding stack\n");
  }
  stack->element = tmp;
  stack->capacity = capacity;
}

void push_stack(Stack** stack, int val) {
  if ((*stack)->size == (*stack)->capacity) {
    expand_stack(*stack);
  }
  (*stack)->element[(*stack)->size++] = val;
}
int pop_stack(Stack* stack) {
  if (is_empty(*stack)) {
    printf("Error: empty stack\n");
    exit(1);
  }
  int index = stack->size - 1;
  stack->size--;
  return stack->element[index];
}
int peek_stack(Stack stack) {
  if (is_empty(stack)) {
    printf("Error: empty stack\n");
    exit(1);
  }
  return stack.element[stack.size - 1];
}
bool is_empty(Stack stack){
    return stack.size == 0;
}
