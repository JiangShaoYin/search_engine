#include <func.h>

void dfs_rm (const char* path);
int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    
    dfs_rm(argv[1]);

    return 0;
}

void dfs_rm(const char* path){
    DIR* pdir = opendir(path);
    ERROR_CHECK(pdir,NULL,"opendir");

    struct dirent * pdirent;
    errno = 0;
    while((pdirent = readdir(pdir)) != NULL){
        if(pdirent->d_name[0] == '.'){
            continue;
        }
        char name[256];
        sprintf(name,"%s/%s",path,pdirent->d_name);

        if(pdirent->d_type == DT_DIR){
            dfs_rm(name);
        }else{
            unlink(name);
        }
    }
    rmdir(path);
    closedir(pdir);
}

