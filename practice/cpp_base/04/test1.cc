#include <iostream>
using namespace std;

class Singleton{
public:
    static Singleton* getInstance() {
        if(_instanse == nullptr){
            _instanse = new Singleton();
        }
        return _instanse;
    }

    static void destroyInstance() {
        if(_instanse != nullptr){
            delete _instanse;
            _instanse = nullptr;
        }
    }

private:
    Singleton(){}
    Singleton(const Singleton &);
    Singleton& operator=(const Singleton &);
    static Singleton* _instanse;
};
Singleton * Singleton::_instanse = nullptr;
int main(){
    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();
    cout << p1 << endl;
    cout << p2 << endl;
    return 0;
}

