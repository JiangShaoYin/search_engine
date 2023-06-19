#include <func.h>
#include "homework3.h"

int main(int argc, const char* argv[]){
    ARGC_CHECK(argc, 2);
    
    int fd = open(argv[1], O_RDWR|O_CREAT, 0666);
    ERROR_CHECK(fd,-1,"open");

    Student s[3] = {{1,"tom",99.5},{2,"titi",99.3},{3,"haha",99.9}};
    
    for(int i = 0; i < 3; i ++){
        write(fd,&s[i],sizeof(Student));
    }


    lseek(fd,0,SEEK_SET);

    Student stu;
    while(1){
        int ret = read(fd, &stu, sizeof(stu));
        if(ret == 0){
            break;
        }

        printf("ID: %d, name: %s, score: %f\n ",stu.no, stu.name,stu.score);
    }

    return 0;
}

