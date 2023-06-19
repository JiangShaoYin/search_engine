#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 3);
    mode_t mode;
    sscanf(argv[2],"%o",&mode);
    int res = chmod(argv[1],mode);
    ERROR_CHECK(res,-1,"chmod");
    return 0;
}

