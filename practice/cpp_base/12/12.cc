#include <iostream>
using namespace std;

class A {
 public:
  virtual void func(int val = 333) { cout << "A->" << val << endl; }
  virtual void test() { func();}
 private:
  long _a;
};

class B
    : public A {
 public:
  virtual void func(int val = 10) { cout << "B->" << val << endl; }
 private:
  long _b;
};

class C
    : public B {
  virtual void func(int val = 10) { cout << "C->" << val << endl; }
};

/*
运行结果为：
B->333
B->10
说明：
1.虚函数的默认参数是静态绑定的，即在编译时就已经确定了，而不是动态绑定的。
2.虚函数的默认参数是根据指针或者引用的类型来确定的，而不是根据对象的类型来确定的。
3.调用虚函数时，若使用默认参数，则使用的是静态绑定的默认参数，而不是动态绑定的默认参数，即使用的是指针或者引用的类型来确定的默认参数。
*/
int main(void) {
  B b;
  A *p1 = (A *)&b;
  B *p2 = &b;
//   A & a = b;
//   a.func();
  p1->func();
  p2->func();
  return 0;
}