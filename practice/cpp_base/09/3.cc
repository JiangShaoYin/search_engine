#include <iostream>
using std::cout;
using std::endl;

class Singleton {
    class AutoRelease {
        public:
            AutoRelease(){cout << "AutoRelease" << endl;}
            ~AutoRelease(){
                cout << "~AutoRelease()" << endl;
                if(_pInstance){
                    delete _pInstance;
                    _pInstance = nullptr;
                }
            }
    };
public:
    static Singleton * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
private:
    Singleton(){ cout << "Singleton" << endl; }
    ~Singleton() { cout << "~Singleton" << endl; }
    static Singleton * _pInstance;
    static AutoRelease* au;
};

Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease* Singleton::au = new Singleton::AutoRelease();

int main() {
    Singleton * s = Singleton::getInstance();
    Singleton * s1 = Singleton::getInstance();
    return 0;
}
