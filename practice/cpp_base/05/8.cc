#include <iostream>
using namespace std;

/* 实现一个类只能生成堆对象，不能生成栈对象的代码，并能做到正常回收该堆对象。*/

class Point {
    // 栈对象要有public的析构函数与构造函数
    // 堆对象要有public的operator new和构造函数
    // 不能生成栈对象，则析构函数需要被私有化
    // 又因为需要回收堆对象，所以需要在类内定义一个public的用于回收的函数
public:
    Point()
        :_ix(0)
         ,_iy(0){
             cout << "Point()" << endl;
         }
    Point(int x, int y)
        :_ix(x)
         ,_iy(y) {
             cout << "Point(int x, int y)" << endl;
         }
    void* operator new(size_t sz) {
        cout << "operator new" << endl;
        return malloc(sizeof(Point));
    }
    void operator delete(void *p) {
        cout << "operator delete" << endl;
        free(p);
        p = nullptr;
    }
    void destroy() {
        delete this;
    }
    void print() {
        cout << "x:" << _ix << " y:" << _iy << endl;
    }

private:
    ~Point(){
        cout << "~Point()" << endl;
    }
    int _ix;
    int _iy;
};

int main()
{
    Point *p = new Point(1,2);
    p->print();
    p->destroy();
    // Point p1(1,2); // error
    return 0;
}

