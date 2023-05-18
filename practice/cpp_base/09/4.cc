#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton * getInstanse() {
        cout << "getInstanse" << endl;
        if(_pInstanse == nullptr){
            _pInstanse = new Singleton();
            atexit(destroy);
        }
        return _pInstanse;
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
};

Singleton* Singleton::_pInstanse = nullptr;
int main(){
    Singleton *s = Singleton::getInstanse();
    return 0;
}

