#include <iostream>
using namespace std;

/*实现一个类只能生成栈对象，不能生成堆对象的代码*/

class Point {
    // 栈对象要有public的析构函数与构造函数
    // 不能生成堆对象，则operator new和operator delete需要被私有化
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
    ~Point(){
        cout << "~Point()" << endl;
    }
    void print() {
        cout << "x:" << _ix << " y:" << _iy << endl;
    }
private:
    void* operator new(size_t sz);
    void operator delete(void *p);
    int _ix;
    int _iy;
};
int main()
{
    Point p1(1,2);
    p1.print();
    // Point *p2 = new Point(); // error
    // p2->print();
    return 0;
}

