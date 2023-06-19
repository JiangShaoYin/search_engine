#include <math.h>
#include <iostream>
#include <unordered_set>
using namespace std;

template <typename Container>
void display(const Container &con) {
  for (auto &elem : con) {
    cout << elem << "  ";
  }
  cout << endl;
}

void test() {
  // unordered_set的特征
  // 1、key值是唯一的，不能重复
  // 2、key值是没有顺序的
  // 3、底层用到的是哈希
  unordered_set<int> number = {1, 3, 5, 9, 7, 5, 3, 5, 20};
  display(number);
}

class Point {
 public:
  Point(int ix = 0, int iy = 0): _ix(ix), _iy(iy) {}
  float getDistance() const {return hypot(_ix, _iy);}
  int getX() const {return _ix;}
  int getY() const {return _iy;}
  ~Point() {}
  friend std::ostream &operator<<(std::ostream &os, const Point &rhs);
 private:
  int _ix;
  int _iy;
};

std::ostream &operator<<(std::ostream &os, const Point &rhs) {
  os << "(" << rhs._ix
     << " ," << rhs._iy
     << ")";
  return os;
}

namespace std {
template <>
struct hash<Point> {
  size_t operator()(const Point &rhs) const {
    cout << "struct std::hash" << endl;
    return ((rhs.getX() << 1) ^ (rhs.getY() << 2));
  }
};  // end ofn struct hash
}  // end of namespace std

bool operator==(const Point &lhs, const Point &rhs) {
  cout << "bool operator==" << endl;
  return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()));
}
void test2() {
  unordered_set<Point> number = {
      Point(1, 2),
      Point(1, 2),
      Point(1, -2),
      Point(-1, 2),
      Point(3, 2)
  };
  display(number);
}

int main(int argc, char **argv) {
  test2();
  return 0;
}