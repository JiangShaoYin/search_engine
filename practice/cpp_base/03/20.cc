#include <iostream>
using namespace std;

/*
设已经有A,B,C,D 4个类的定义，程序中A,B,C,D析构函数调用顺序为？

C c;
void main()
{
    A *pa=new A();
    B b;
    static D d;
    delete pa;
}
*/

class A{
public:
    A(){ cout << "A()" << endl; }
    ~A(){ cout << "~A()" << endl; }
};

class B{
public:
    B(){ cout << "B()" << endl; }
    ~B(){ cout << "~B()" << endl; }
};

class C{
public:
    C(){ cout << "C()" << endl; }
    ~C(){ cout << "~C()" << endl; }
};

class D{
public:
    D(){ cout << "D()" << endl; }
    ~D(){ cout << "~D()" << endl; }
};

C c;
int main()
{
    A *pa=new A();
    B b;
    static D d;
    delete pa;
}
