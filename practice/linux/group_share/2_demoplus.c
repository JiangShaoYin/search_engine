#include <func.h>
#include"stack.h"
#define M 5

int main(int argc, const char* argv[]){
    int origin[] = {3,4,2,7,5};
    int res[M] = {0};
    Stack *s = init_stack();
    for(int i = 0; i < M; ++i){
        while(!is_empty(*s) && peek_stack(*s) >= origin[i]){
            pop_stack(s);
        }
        // 1.s is empty
        // 2.the next element is smaller than origin[i]
        if(is_empty(*s)){
            res[i] = -1;
        }else{
            res[i] = peek_stack(*s);
        }
        push_stack(&s,origin[i]);
    }

    for(int i = 0; i < M; ++i){
        printf("%d ", res[i]);
    }
    printf("\n");
    return 0;
}

