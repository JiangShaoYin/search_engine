#include <func.h>

int main(int argc, const char *argv[]){
    //编写C程序，判断任意两个文件，其内容是否是完全一致的。
    //如果一致，返回0，否则返回-1
    //思路：1.打开两个文件
    //     2.读取两个文件的内容，比较是否一致
    //     3.关闭两个文件
    //     4.返回结果
    if(argc != 3){
        printf("error args\n");
        return -1;
    }
    int fd1 = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd1, -1, "open");
    int fd2 = open(argv[2], O_RDONLY);
    ERROR_CHECK(fd2, -1, "open");
    char buf1[1024] = {0};
    char buf2[1024] = {0};
    int ret;
    while(1){
        ret = read(fd1, buf1, sizeof(buf1));
        if(ret == 0){
            break;
        }
        ERROR_CHECK(ret, -1, "read");
        ret = read(fd2, buf2, sizeof(buf2));
        if(ret == 0){
            break;
        }
        ERROR_CHECK(ret, -1, "read");
        if(strcmp(buf1, buf2)){
            printf("not same\n");
            return -1;
        }
    }
    close(fd1);
    close(fd2);
    printf("same\n");
    return 0;
}