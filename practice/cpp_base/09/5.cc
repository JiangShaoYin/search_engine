#include <iostream>
#include <pthread.h>
using namespace std;

class Singleton{
public:
    static Singleton * getInstanse() {
        cout << "getInstanse" << endl;
        pthread_once(&_once, init);
        return _pInstanse;
    }
    static void init() {
        cout << "init()" << endl;
        _pInstanse = new Singleton();
        atexit(destroy);
    }
    static void destroy() {
        cout << "destroy" << endl;
        if(_pInstanse){
            delete _pInstanse;
            _pInstanse = nullptr;
        }
    }
private:
    Singleton(){ cout << "Singleton" << endl;  }
    ~Singleton() {cout << "~Singleton" << endl; }
    static Singleton * _pInstanse;
    static pthread_once_t _once; 
};

Singleton* Singleton::_pInstanse = nullptr;
pthread_once_t  Singleton::_once = PTHREAD_ONCE_INIT;

int main(){
    Singleton *s = Singleton::getInstanse();
    return 0;
}

