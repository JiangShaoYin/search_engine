#include <func.h>

int main(int argc, const char *argv[]){
    //创建一个文件，里面有100万个字符'1'
    //使用mmap将文件映射到内存中，然后将内存中的内容全部修改为'2'
    //思路：1.创建文件
    //     2.将文件映射到内存中
    //     3.修改内存中的内容
    //     4.关闭文件
    //     5.返回结果
    int fd = open("file", O_RDWR | O_CREAT, 0666);
}