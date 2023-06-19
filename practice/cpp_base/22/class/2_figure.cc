#include <math.h>
#include <functional>
#include <iostream>
using namespace std;

class Figure {
 public:
  // 重新定义的方法
  /* typedef function<void()> DisplayCallback;//C++98写法 */
  using DisplayCallback = function<void()>;  // C++11写法
  using AreaCallback = function<double()>;

  // 使用回调函数的思想进行操作
  // 1、注册回调函数
  void setDisplayCallback(DisplayCallback &&cb) {
    _displayCallback = std::move(cb);
  }

  void setAreaCallback(AreaCallback &&cb) {
    _areaCallback = std::move(cb);
  }

  // 2、执行回调函数
  void handleDisplayCallback() const {
    if (_displayCallback) {
      _displayCallback();
    }
  }

  double handleAreaCallback() const {
    if (_areaCallback) {
      return _areaCallback();
    } else {
      return 0;
    }
  }

 private:
  DisplayCallback _displayCallback;
  AreaCallback _areaCallback;
};

class Rectangle {
 public:
  Rectangle(double length = 0, double width = 0)
      : _length(length), _width(width) {
    cout << "Rectangle(double = 0, double = 0)" << endl;
  }

  void display(int x) const {
    cout << "Rectangle";
  }

  double area() const {
    return _length * _width;
  }

  ~Rectangle() {
    cout << "~Rectangle()" << endl;
  }

 private:
  double _length;
  double _width;
};

class Circle {
 public:
  Circle(double radius = 0)
      : _radius(radius) {
    cout << "Circle(double = 0)" << endl;
  }

  void print() const {
    cout << "Circle";
  }

  double printArea() const {
    return 3.14 * _radius * _radius;
    ;
  }

  ~Circle() {
    cout << "~Circle()" << endl;
  }

 private:
  double _radius;
};

void func(const Figure &fig) {
  fig.handleDisplayCallback();
  cout << "的面积 : " << fig.handleAreaCallback() << endl;
}

int main(int argc, char **argv) {
  Rectangle rectangle(10, 20);
  Circle circle(10);

  Figure fig;
  // 针对的是Rectangle
  fig.setDisplayCallback(bind(&Rectangle::display, &rectangle, 10));
  fig.setAreaCallback(bind(&Rectangle::area, &rectangle));
  func(fig);

  // 针对的是Circle
  fig.setDisplayCallback(bind(&Circle::print, &circle));
  fig.setAreaCallback(bind(&Circle::printArea, &circle));
  func(fig);
  return 0;
}