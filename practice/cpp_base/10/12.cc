#include <iostream>
using namespace std;

/*
编写一个圆类Circle，该类拥有：
① 1个成员变量，存放圆的半径；
② 两个构造方法 
    Circle( ) // 将半径设为0 
    Circle(double r ) //创建Circle对象时将半径初始化为r 
③ 三个成员方法 
    double getArea( ) //获取圆的面积 
    double getPerimeter( ) //获取圆的周长 
    void show( ) //将圆的半径、周长、面积输出到屏幕
*/

class Circle {
public:
    Circle()
    : _r(0){}
    Circle(double r)
    :_r(r){}
    double getArea() const {
        return 3.14 * _r * _r;
    }
    double getPerimeter() const {
        return 2 * 3.14 * _r;
    }
    void show() const {
        cout << "r = " << _r 
             << ", area = " << getArea() 
             << ", perimeter = " << getPerimeter() << endl;
    }
private:
    double _r;
};

/*
编写一个圆柱体类Cylinder，它继承于上面的Circle类，还拥有：
① 1个成员变量，圆柱体的高；
② 构造方法
Cylinder (double r, double h) //创建Circle对象时将半径初始化为r
③ 成员方法
double getVolume( ) //获取圆柱体的体积
void showVolume( ) //将圆柱体的体积输出到屏幕
编写应用程序，创建类的对象，分别设置圆的半径、圆柱体的高，计算并分别显示圆半径、圆面积、圆周长，圆柱体的体积。
*/
class Cylinder
:public Circle {
public:
    Cylinder(double r, double h)
    :Circle(r), _h(h){}
    double getVolume() const {
        return getArea() * _h;
    }
    void showVolume() const {
        cout << "volume = " << getVolume() << endl;
    }
private:
    int _h;
};
int main(){
    Cylinder c(1, 2);
    c.show();
    c.showVolume();
    return 0;
}