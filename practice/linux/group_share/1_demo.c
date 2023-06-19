#include <func.h>
#define N 5
int main(){
    int origin[] = {3,4,2,7,5};
    int res[N] = {0};
    for(int i = 0; i < N;++i){
        res[i] = -1;
        for(int j = i - 1; j>= 0; j--){
            if(origin[j] < origin[i]){
                res[i] = origin[j];
                break;
            }
        }
    }
    for(int i = 0; i < N; ++i){
        printf("%d ",res[i]);
    }
    printf("\n");
    return 0;
}

