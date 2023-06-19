#include <iostream>
using namespace std;

template <class T, int qSize = 10>
class Queue{
public:
    Queue()
        :_front(0)
         ,_tail(0)
         ,_size(0)
         ,_data(new T[qSize]()){}
    ~Queue();
    bool empty();
    bool full();
    void push(T value);
    void pop();
    T & front();
private:
    int _front, _tail,_size;
    T * _data;
};

template <class T, int qSize>
Queue<T,qSize>::~Queue(){
    if(_data){
        delete [] _data;
        _data = nullptr;
    }
}
template <class T, int qSize>
bool Queue<T,qSize>::empty(){
    return _size == 0;
}
template <class T, int qSize>
bool Queue<T,qSize>::full(){
    return _size == qSize - 1;
}
template <class T, int qSize>
void Queue<T, qSize>::push(T value){
    if(!full()){
        _data[_tail] = value;
        _tail = (_tail + 1) % qSize;
        ++_size;
    }else{
        cout << "the queue is full, cannot push any more data" << endl;
    }
}
template <class T, int qSize>
void Queue<T,qSize>::pop(){
    if(!empty()){
        _front = (_front + 1) % qSize;
        --_size;
    }else{
        cout << "the queue is empty, cannot pop any data" << endl;
    }
}
template <class T, int qSize>
T & Queue<T, qSize>::front(){
    return _data[_front];
}

int main(){
    Queue<int> q;
    for (int i = 0; i < 11; ++i){
        q.push(i);
    }

    while(!q.empty()){
        cout << q.front() << endl;
        q.pop();
    }
    cout << "queue empty? " << q.empty() << endl;
    return 0;
}
