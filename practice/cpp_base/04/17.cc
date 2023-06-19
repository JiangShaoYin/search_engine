#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton *getInstanse() {
        if(_instanse == nullptr){
            _instanse = new Singleton();
        }
        return _instanse;
    }
    
    static void destroy(){
        if(_instanse != nullptr){
            free(_instanse);
            _instanse = nullptr;
        }
    }
private:
    Singleton(){};
    ~Singleton();
    Singleton(const Singleton & rhs);
    Singleton & operator = (const Singleton&);
    static Singleton * _instanse;
};

Singleton * Singleton::_instanse = nullptr;

int main(void) {
    Singleton* p1 = Singleton::getInstanse();
    Singleton* p2 = Singleton::getInstanse();
    cout << p1 << endl;
    cout << p2 << endl;

    Singleton::destroy();
    return 0;
}    
