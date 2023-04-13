#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,3);

    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open fdr");

    int mkres = mkdir(argv[2],0777);
    ERROR_CHECK(mkres,-1,"mkdir");
    //DIR *pdir = opendir(argv[2]);
    int chdirres = chdir(argv[2]);
    ERROR_CHECK(chdirres,-1,"changdir");

    char buf[4096];
    int name_size;
    read(fdr,&name_size,sizeof(int));
    read(fdr,buf,name_size);
    int fdw = open(buf,O_WRONLY|O_CREAT, 0666);

    int length_size;
    read(fdr,&length_size,sizeof(int));
    off_t length;
    read(fdr,&length,length_size);
    ftruncate(fdw,length);

    while(1){
        memset(buf,0,sizeof(buf));
        int retr = read(fdr,buf,sizeof(buf));
        ERROR_CHECK(retr,-1,"read");
        if(retr == 0){
            break;
        }
        write(fdw,buf,retr);
    }
    return 0;
}

