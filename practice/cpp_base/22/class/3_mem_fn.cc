#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::copy;
using std::cout;
using std::endl;
using std::for_each;
using std::remove_if;
using std::vector;

class Number {
 public:
  Number(int data = 0) : _data(data) { }
  void print() const { cout << _data << "  "; }
  // 是不是偶数
  bool isEven() const { return (0 == _data % 2);  }
  ~Number() {}
 private:
  int _data;
};

void test() {
  vector<Number> vec = {1,2,3,4,5};
  Number num(10);
  using namespace std::placeholders;
  // 成员函数可以使用bind绑定
  for_each(vec.begin(), vec.end(), std::bind(&Number::print, _1)); 
  // 成员函数可以使用mem_fn包装
  /* for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print)); */
  cout << endl;

  // 所有的偶数删除
  cout << "删除掉所有的偶数" << endl;
    // 成员函数可以使用mem_fn包装
  auto it = remove_if(vec.begin(), vec.end(),
                      std::mem_fn(&Number::isEven));
  vec.erase(it, vec.end());
  for_each(vec.begin(), vec.end(), std::mem_fn(&Number::print));
  cout << endl;
}

int main(int argc, char **argv) {
  test();
  return 0;
}

