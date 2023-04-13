#include <func.h>

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc,3);

    int fd = open(argv[1],O_WRONLY);
    ERROR_CHECK(fd,-1,"open fd");
    // 打开文件，获取文件名称和大小
    // 传输文件名称长度和名称
    // 传输文件大小长度和文件大小
    // 读取文件内容，传输文件内容
    int name_size = strlen(argv[2]);
    write(fd,&name_size,sizeof(name_size));
    write(fd,argv[2],name_size);

    struct stat file;
    int res = stat(argv[2],&file);
    ERROR_CHECK(res,-1,"stat");
    off_t length = file.st_size;
    int length_size = sizeof(off_t);
    write(fd,&length_size, sizeof(length_size));
    write(fd,&length,length_size);

    int fd2 = open(argv[2],O_RDONLY);
    ERROR_CHECK(fd2,-1,"open fd2");
    char buf[4096];
    while(1){
        memset(buf,0,sizeof(buf));
        int retr = read(fd2,buf, sizeof(buf));
        ERROR_CHECK(retr,-1,"readfile");
        if(retr == 0){
            break;
        }
        write(fd,buf,retr);
    }
    return 0;
}

