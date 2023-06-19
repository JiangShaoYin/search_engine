#include <func.h>
#include "stack.h"
#define M 8
int main(int argc, const char* argv[]){
    int origin[] = {73,74,75,71,69,72,76,73};
    int answer[M] = {0};
    Stack *s = init_stack();
    for(int i = M -1; i >= 0 ; --i){
        while(!is_empty(*s) && origin[peek_stack(*s)] <= origin[i]){
            pop_stack(s);
        }        
        if(is_empty(*s)){
            answer[i] = 0;
        }else{
            answer[i] = peek_stack(*s) - i;
        }
        push_stack(&s, i);
    }

    for(int i = 0; i < M; ++i){
        printf("%d ",answer[i]);
    }
    printf("\n");

    return 0;
}

