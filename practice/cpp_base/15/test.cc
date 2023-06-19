#include <iostream>
using namespace std;

template <class... Args>
void printTotalSize(Args... args) {
  cout << sizeof...(Args) << endl;
  cout << sizeof...(args) << endl;
}
void test() {
  printTotalSize();
  printTotalSize(3.14159);
  printTotalSize('a', "hello");
  printTotalSize(1, 1.2, "hello,world");
}

int main() {
  test();
  return 0;
}