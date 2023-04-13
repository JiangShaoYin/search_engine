#include <func.h>

int main(){
    char *buf = getcwd(NULL,0);
    puts(buf);
    free(buf);
    return 0;
}
