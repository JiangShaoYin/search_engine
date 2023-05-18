#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
using std::bind;

class Func{
public:
    void func3() {
        cout << "Func::func3()" << endl;
    }

    void func4(int a, int b) {
    cout << "Func::func4(): a = " << a << ", b = " << b << endl;
}
};

void func0() {
    cout << "func0()" << endl;
}

int func1(int a, int b) {
    cout << "func1(): a = " << a << ", b = " << b << endl;
    return a + b;
}

int main() {
    // 普通函数
    function<void()> f0 = func0;
    f0();
    // 普通有参函数方法一：不使用bind
    function<int(int, int)> f1 = func1;
    int res = f1(1, 2);
    cout << "res = " << res << endl;
    // 普通有参函数方法二：使用bind 使用bind，funcrion中的参数就不用写了
    function<int()> f2 = bind(func1, 3, 4);
    res = f2();
    cout << "res = " << res << endl;
    // function<int(int, int)> f22 = bind(func1, 5, 9); 这样执行的时候，f22(5, 6)中的5, 6是无效的
    // res = f22(5, 6);
    // cout << "res = " << res << endl;

    // 无参类成员函数
    Func func;
    function<void()> f3 = bind(&Func::func3, &func);
    f3();
    // 有参类成员函数 方法一
    function<void()> f4 = bind(&Func::func4, &func, 10, 20);
    f4();
    // 有参类成员函数 方法二
    using namespace std::placeholders;
    function<void(int, int)> f5 = bind(&Func::func4, &func, _1, _2);
    f5(100, 200);
    return 0;
}