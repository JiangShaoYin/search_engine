#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    char* buf = getcwd(NULL,0);
    ERROR_CHECK(buf,NULL, "getchar");
    puts(buf);

    int res = chdir(argv[1]);
    ERROR_CHECK(res,-1,"chdir");
    buf = getcwd(NULL,0);
    ERROR_CHECK(buf,NULL,"getchar");
    puts(buf);
    free(buf);
    return 0;
}
