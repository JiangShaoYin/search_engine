#include <iostream>
using namespace std;

class Singleton {
public:
    static Singleton * getInstance() {
        if(_pInstance == nullptr){
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
    static void destroy() {
        cout << "destroy instance" << endl;
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Singleton(){
        cout << "Create Instance" << endl;
    }
    ~Singleton(){
        cout << "~Singleton" << endl;
    }
    static Singleton * _pInstance;
};

class AutoRelease {
public:
    AutoRelease(Singleton *p) 
    :_sing(p){};
   ~AutoRelease() {
       Singleton::destroy(); 
   }
private:
   Singleton * _sing;
};

Singleton* Singleton::_pInstance = nullptr;

int main(){
    AutoRelease au(Singleton::getInstance());
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    printf("s1 = %p\n", s1);
    printf("s2 = %p\n", s2);
    // Singleton::destroy();
    return 0;
}

