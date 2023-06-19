#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 2);
    int res = rmdir(argv[1]);
    ERROR_CHECK(res,-1,"rmdir");
    return 0;
}

