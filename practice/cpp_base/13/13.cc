#include <iostream>
#include <math.h>
using namespace std;

class Figure {
 public:
  virtual string getName() const = 0;
  virtual double getArea() const = 0;
};
void display(Figure& fig) {
  cout << fig.getName()
       << "的面积是:"
       << fig.getArea() << endl;
}

class Rectangle
    : public Figure {
 public:
  Rectangle(int w, int h) : _width(w), _height(h) {}
  string getName() const {
    return "矩形";
  }
  double getArea() const {
    return _width * _height;
  }

 private:
  int _width, _height;
};

class Circle
    : public Figure {
 public:
  Circle(int r) : _r(r) {}
  string getName() const {
    return "圆形";
  }
  double getArea() const {
    return 3.14 * _r * _r;
  }

 private:
  int _r;
};

class Triangle
    : public Figure {
 public:
  Triangle(int a, int b, int c) : _a(a), _b(b), _c(c) {}
  string getName() const {
    return "三角形";
  }
  double getArea() const {
    double p = (_a + _b + _c) / 2.0;
    return sqrt(p * (p - _a) * (p - _b) * (p - _c));
  }

 private:
  int _a, _b, _c;
};

void test() {
  Rectangle r(10, 20);
  Circle c(15);
  Triangle t(3, 4, 5);
  display(r);
  display(c);
  display(t);
}

int main(){
    test();
    return 0;
}