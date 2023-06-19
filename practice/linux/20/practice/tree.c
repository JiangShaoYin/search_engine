#include <func.h>

void print_tree(const char* path, int space);
int directories_cnt = 0;
int file_cnt = 0;
int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,2);
    puts(argv[1]);
    print_tree(argv[1], 4);
    printf("\n directory_cnt: %d   file_cnt: %d \n", directories_cnt, file_cnt);
    return 0;
}

void print_tree(const char* path, int space){
    DIR *pdir = opendir(path);
    ERROR_CHECK(pdir,NULL,"opendir");

    struct dirent *pdirent;
    errno = 0;
    while((pdirent = readdir(pdir)) != NULL){
    
        if(pdirent->d_name[0] == '.'){
            continue;
        }
        for(int i = 0; i < space; i++){
            printf(" ");
        }
        puts (pdirent->d_name);
        if(pdirent->d_type == DT_DIR){
            directories_cnt++;
            char name[256];
            sprintf(name,"%s/%s",path,pdirent->d_name);
            print_tree(name, space + 4);
        }else{
            file_cnt++;
        }
    }
    if(errno){
        perror("readdir");
        closedir(pdir);
        exit(1);
    }
    closedir(pdir);
}

