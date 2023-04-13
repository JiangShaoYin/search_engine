#include <func.h>
#include "stack.h"
#define M 12
int main(int argc, const char* argv[]){
    int origin[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int res = 0;
    Stack *s = init_stack();
    for(int i = 0; i < M; ++i){
        while(!is_empty(*s) && origin[peek_stack(*s)] < origin[i]){
            int bottom = origin[pop_stack(s)];
            if(is_empty(*s)) break;
            int h = (origin[i] < origin[peek_stack(*s)]?origin[i]:origin[peek_stack(*s)]) - bottom;
            int w = i - peek_stack(*s) - 1;
            res += h * w;
        }
        push_stack(&s,i);
    }
    printf("%d\n", res);
    return 0;
}

