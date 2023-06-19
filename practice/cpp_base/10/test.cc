#include <iostream>
using namespace std;

class Base {
 public:
  Base(int x = 0)
      : _ix(x) {
    _ix = 33;
    std::cout << "Base(int)" << std::endl;
  }

 private:
  int _ix;
};

class Base2
: public Base {
 public:
  Base2(int x = 0, int y = 0)
      : Base(x) 
      ,_iy(y) {
    std::cout << "Base2(int, int)" << std::endl;
  }

 private:
  int _iy;
};

class Base1 
: virtual public Base {
 public:
  Base1(int x = 0, int y = 0)
      : Base(x) 
      ,_iy(y) {
    std::cout << "Base1(int, int)" << std::endl;
  }

 private:
  int _iy;
};

int main() {
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(Base1) = " << sizeof(Base1) << endl;
    cout << "sizeof(Base2) = " << sizeof(Base2) << endl;
    return 0;
}