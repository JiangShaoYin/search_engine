#include <iostream>
using namespace std;
/*
编写一个程序计算两个给定的长方形的周长和面积。
*/
class Rectangle{
private:
    double _length;
    double _width;
public:
    Rectangle(double length, double width){
        _length = length;
        _width = width;
    }
    double getArea(){
        return _length * _width;
    }
};

int main(){
    Rectangle rectangle1(4, 40);
    Rectangle rectangle2(3.5, 35.9);
    
    cout << "rectangle1's area is " << rectangle1.getArea() << endl;
    cout << "rectangle2's area is " << rectangle2.getArea() << endl;
    
    return 0;
}