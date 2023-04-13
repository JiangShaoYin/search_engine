#include <func.h>
#include "stack.h"
#define M 6

int main(int argc, const char* argv[]){
    int origin[] = {2,1,5,6,2,3};
    Stack *s = init_stack();
    int max = 0;
    int w = 0, h = 0;
    for(int i = 0; i < M; ++i){
        while(!is_empty(*s) && origin[peek_stack(*s)] > origin[i]){
            h = origin[pop_stack(s)];
            w = i - (is_empty(*s) ? -1 : peek_stack(*s)) - 1;
            max = max > h * w? max: h * w;
        }
        push_stack(&s,i);
    }
    int r = peek_stack(*s);
    while(!is_empty(*s)){
        h = origin[pop_stack(s)];
        w = r - (is_empty(*s) ? -1 : peek_stack(*s));
        max = max > h * w ? max : h * w;
    }
    printf("%d\n", max);
    return 0;
}

