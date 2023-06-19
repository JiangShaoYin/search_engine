#include <iostream>
using namespace std;

class Stack {
public:
    Stack(){
        topIndex = -1;
    }
    bool empty(){
        //判断栈是否为空
        return topIndex == -1;
    }	
    bool full(){
        //判断栈是否已满
        return topIndex == 1;
    }
    void push(int a){
        //元素入栈
        if(full()){
            cout << "栈已满" << endl;
            return;
        }
        data[++topIndex] = a;
    }
    void pop(){
        //元素出栈
        if(empty()){
            cout << "栈已空" << endl;
            return;
        }
        topIndex--;
    }
    int  top(){
        //获取栈顶元素
        if(empty()){
            cout << "栈已空" << endl;
            return -1;
        }
        return data[topIndex];
    }
private:
    int data[2];
    int topIndex;
};

int main(){
    Stack stack;
    cout << "is empty " << stack.empty() << endl;
    cout << "is full " << stack.full() << endl;
    stack.push(1);
    cout << "push the first element 1" << endl;
    stack.push(2);
    cout << "push the second element 2" << endl;
    cout << "is full " << stack.full() << endl;
    cout << "top " << stack.top() << endl;
    stack.pop();
    cout << "is empty " << stack.empty() << endl;
    cout << "top " << stack.top() << endl;
    stack.pop();
    cout << "is empty " << stack.empty() << endl;
    return 0;
}
