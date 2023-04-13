#include <func.h>

int main(int argc, const char *argv[]){
    // rm argv[1] file
    // 1. judge argv[1] is file or dir
    // 2. if file, remove it
    // 3. if dir, remove it
    // 4. if not exist, print error
    struct stat buf;
    int ret = stat(argv[1], &buf);
    ERROR_CHECK(ret, -1, "stat");
    if(S_ISREG(buf.st_mode)){
        ret = unlink(argv[1]);
        ERROR_CHECK(ret, -1, "unlink");
    }else if(S_ISDIR(buf.st_mode)){
        DIR *pdir = opendir(argv[1]);
        ERROR_CHECK(pdir, NULL, "opendir");
        struct dirent *pdirent;
        errno = 0;
        while((pdirent = readdir(pdir)) != NULL){
            if(pdirent->d_name[0] == '.'){
                continue;
            }
            char name[256];
            sprintf(name, "%s/%s", argv[1], pdirent->d_name);
            ret = remove(name);
            ERROR_CHECK(ret, -1, "remove");
        }
        ret = rmdir(argv[1]);
        ERROR_CHECK(ret, -1, "rmdir");
        closedir(pdir);
    }else{
        printf("not file or dir\n");
    }
    return 0;
    
}