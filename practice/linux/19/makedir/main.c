#include <stdio.h>
#include "main.h"

int main()
{
    int a = 1;
    int b = 3;
    printf("add(%d,%d) = %d\n",a,b,add(a,b));
    printf("add(%d,%d) = %d\n",a,b,sub(a,b));
    printf("add(%d,%d) = %d\n",a,b,mul(a,b));
    printf("add(%d,%d) = %d\n",a,b,div(a,b));
    return 0;
}
