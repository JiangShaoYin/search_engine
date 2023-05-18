#include <functional>
#include <iostream>

using std::bind;
using std::cout;
using std::endl;
using std::function;

// 普通函数(非成员函数)
int add(int x, int y) {
  cout << "int add(int, int)" << endl;
  return x + y;
}

class Example {
 public:
  int add(int x, int y) {
    cout << "int Example::add(int, int)" << endl;
    return x + y;
  }

  // 数据成员
  int data = 100;  // C++11
};

void func(int x1, int x2, int x3, const int &x4, int x5) {
  cout << x1 << x2 << x3 << x4 << x5 << endl;
}

void test0() {
  int number = 10;
  using namespace std::placeholders;
  // 占位符本身会表示的是形参的位置
  // 占位符中的数字代表的是实参的位置
  // bind绑定函数的时候，默认会使用值传递
  // std::ref = referenece，称为引用的包装器
  // std::cref = const referenece，称为引用的包装器
  auto f = bind(func, 1, _3, _1, std::cref(number), number);
  number = 33;
  f(20, 40, 50, 60, 80);  // 多余的参数就直接丢掉
  /* f(20, 40, 50); */
}

void test1() {
  /* vector<int> number = {1, 2, 3}; */
  // 函数的形态、类型、标签
  // 函数类型：函数的返回类型 + 函数的参数列表
  // add函数的类型：int(int, int)
  // f的函数类型：int()
  // bind可以改变函数的形态（重要）：
  // 可以改变函数参数的个数(减少函数的参数个数)
  // function可以存函数类型，所以可以将function称为函数的容器
  function<int()> f = bind(&add, 1, 2);
  cout << "f() = " << f() << endl;

  Example ex;
  // add函数的形态：int(this, int, int)
  // f3的函数类型：int()
  function<int()> f3 = bind(&Example::add, &ex, 10, 20);
  cout << "f3() = " << f3() << endl;

  using namespace std::placeholders;  // 占位符
  // add函数形态：int(int, int)
  // f4的函数类型：int(int)
  function<int(int)> f4 = bind(add, 1, _1);
  cout << "f4(9) = " << f4(9) << endl;

  // bind不仅可以绑定到普通函数，也可以绑定到成员函数，甚至
  // 还可以绑定到数据成员
  Example ex2;
  f3 = bind(&Example::data, &ex2);
  cout << "f3() = " << f3() << endl;
}

int main(int argc, char **argv) {
  test0();
  return 0;
}
