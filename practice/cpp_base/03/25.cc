#include <iostream>
using namespace std;

/*
定义一个学生类，其中有3个数据成员：学号、姓名、年龄，以及若干成员函数。
同时编写main函数，使用这个类，实现对学生数据的赋值和输出。
*/
class Student{
public:
    Student(int id, string name, int age){
        _id = id;
        _name = name;
        _age = age;
    }
    
    void print(){
        cout << "id:" << _id << endl;
        cout << "name:" << _name << endl;
        cout << "age:" << _age << endl;
    }
private:
    int _id;
    string _name;
    int _age;
};

int main(){
    Student stu(1, "zhangsan", 20);
    stu.print();
    
    return 0;
}