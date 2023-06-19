#include <functional>
#include <iostream>
using namespace std;

class Test {
 public:
  void print(int x) {
    cout << "Test::print(int): " << x << endl;
  }
};

int main() {
  Test t;
  // 对象进行取地址
  auto f = bind(&Test::print, &t, 10);
  f();
  // 对象不进行取地址
  auto f2 = bind(&Test::print, t, 20);
  f2();
  return 0;
}