#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

template<class T, class... Args>
class Singleton {
public:
    static T * getInstance(Args... args) {
        if(_pInstance == nullptr){
            _pInstance = new T(args...);
        }
        return _pInstance;
    }

    static void  destroy() {
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Singleton() {};
    ~Singleton() {};
    static T * _pInstance;
};

template<class T, class... Args>
T * Singleton<T, Args...>::_pInstance = nullptr;

// 有些疑惑的点：
// 在创建了computer类之后，为啥point类还能创建，_pInstance是static变量，这个时候的pInstance是nullptr吗
// 如果模版是在编译时替换，那么根据我传进去的T不同，会在编译时生成不同的Singleton类吗，重名问题？
// 如果在这里调用了destroy方法，destroy的是point的单例还是computer的单例呢

class Point {
public:
    Point(int x, int y) :_x(x) ,_y(y) {}
private:
    int _x;
    int _y;
};
class Computer {
public:
    Computer(string brand, float price) :_brand(brand) ,_price(price) {}
private:
    string _brand;
    float _price;
};

int main(void) {
    Computer *pc1 = Singleton<Computer, string, float>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer, string, float>::getInstance("Xiaomi", 6666);
    assert(pc1 == pc2) ;
    cout << "(pc1 == pc2): " << (pc1 == pc2) << endl;
    Point *pt3 = Singleton<Point, int, int>::getInstance(1, 2);
    Point *pt4 = Singleton<Point, int, int>::getInstance(1, 2);
    assert(pt3 == pt4);
    cout << "(pt3 == pt4): " << (pt3 == pt4) << endl;
    return 0;
} 
