#include <iostream>
#define N 10
using namespace std;

class Queue {
public:
    Queue(){
        _frontIndex = 0;
        _backIndex = 0;
        _size = 0;
    }
    bool empty(){
        //判断栈是否为空
        return _frontIndex == _backIndex;
    }	
    bool full(){
        //判断栈是否已满
        return _size == N - 1;
    }
    void push(int a){
        //元素入队
        if(full()){
            cout << "队列已满" << endl;
            return;
        }
        _data[_backIndex] = a;
        _backIndex = (_backIndex + 1) % N;
        _size++;
        cout << "push element" << endl;
    }
    void pop(){
        //元素出队
        if(empty()){
            cout << "队列已空" << endl;
            return;
        }
        _frontIndex = (_frontIndex + 1) % N;
        _size--;
        cout << "pop element" << endl;
    }
    int  front(){
        //获取队头元素
        if(empty()){
            cout << "队列已空" << endl;
            return -1;
        }
        return _data[_frontIndex];
    }
    int  back(){
        //获取队尾元素
        if(empty()){
            cout << "队列已空" << endl;
            return -1;
        }
        return _data[(_backIndex - 1) % N];
    }
private:
    int _data[N];
    int _frontIndex;
    int _backIndex;
    int _size;
};

int main(){
    Queue queue;
    cout << "is empty " << queue.empty() << endl;
    cout << "is full " << queue.full() << endl;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    
    cout << "is full " << queue.full() << endl;
    cout << "front " << queue.front() << endl;
    cout << "back " << queue.back() << endl;
    queue.pop();
    cout << "is empty " << queue.empty() << endl;
    cout << "front " << queue.front() << endl;
    cout << "back " << queue.back() << endl;
    queue.pop();
    cout << "front " << queue.front() << endl;
    cout << "back " << queue.back() << endl;
    cout << "is empty " << queue.empty() << endl;
    return 0;
}