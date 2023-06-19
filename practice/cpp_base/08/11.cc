#include <iostream>
using namespace std;

class Base {
 public:
  Base(int num = 0)
      : _num(num) { }
  ~Base() { }
  int getter() {return _num;}
 private:
  int _num;
};

int operator+(Base &b1, Base &b2) { return b2.getter() - b1.getter(); }

int main() {
  int i = 2;
  int j = 7;

  Base x(i);
  Base y(j);
  cout << (x + y == j - i) << endl;
  return 0;
}