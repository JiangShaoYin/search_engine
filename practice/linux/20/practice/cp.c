#include <func.h>

void copyFile(const char*, const char*);
void copyDir(const char*, const char*);

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,3);
    int res = mkdir(argv[2], 0775);
    ERROR_CHECK(res, -1, "mkdir");
    copyDir(argv[1],argv[2]);
    return 0;
}

void copyFile(const char* c1, const char* c2){
    FILE* fp1 = fopen(c1,"r");
    ERROR_CHECK(fp1,NULL,"fopen");
    FILE* fp2 = fopen(c2,"w");
    ERROR_CHECK(fp2,NULL,"fopen");
    fseek(fp1,0l,SEEK_END);
    long distance = ftell(fp1);
    rewind(fp1);
    char* input =(char*) calloc(distance+1, sizeof(char));

    fread(input, 1, distance + 1, fp1);
    fwrite(input,1,distance + 1, fp2);
    fclose(fp1);
    fclose(fp2);
}
void copyDir(const char* c1, const char* c2){
    DIR *pdir = opendir(c1);
    ERROR_CHECK(pdir, NULL, "opendir");
    struct dirent* prent;
    errno = 0;
    while((prent = readdir(pdir)) != NULL){
        if(prent->d_name[0] == '.'){
            continue;
        }
        char name1[256];
        sprintf(name1,"%s/%s",c1, prent->d_name);
        char name2[256];
        sprintf(name2,"%s/%s",c2, prent->d_name);
        if(prent->d_type == DT_DIR ){
            int res = mkdir(name2 , 0775);
            ERROR_CHECK(res, -1, "mkdir");
            copyDir(name1,name2 );       
        } else{
           copyFile(name1, name2 ); 
        }
    }
        
    if(errno){
        perror("readdir");
        closedir(pdir);
        exit(1);
    }
    closedir(pdir);
}

