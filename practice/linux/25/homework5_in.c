#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    DIR* pdir = opendir(argv[1]);
    struct dirent* dir;
    while((dir = readdir(pdir))!= NULL){
        if(dir->d_name[0] == '.'){
            continue;
        }
        printf("%s\n",dir->d_name);
    }
    return 0;
}

