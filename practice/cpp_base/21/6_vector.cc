#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/*
std::allocator的用法之后,实现自定义的Vector类

接口形式：

template<typename T> 
class Vector 
{ 
public:     
    Vector();     
    ~Vector();          
    void push_back(const T &);      
    void pop_back();         
    int size();     
    int capacity(); 
private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};
*/

template<typename T>
class MyVector
{
public:
    MyVector();
    ~MyVector();
    void push_back(const T &);
    void pop_back();
    int size();
    int capacity();
    int operator[](int index){
        if (index < 0 || index >= size()) {
            cout << "index out of range" << endl;
            return -1;
        }
        return _start[index];
    }
private:
    void reallocate();
private:
    static std::allocator<T> _alloc;
    T *_start;                 //指向数组中的第一个元素
    T *_finish;                //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};

template<typename T>
std::allocator<T> MyVector<T>::_alloc;

template<typename T>
MyVector<T>::MyVector()
{
    _start = _finish = _end_of_storage = nullptr;
}

template<typename T>
MyVector<T>::~MyVector()
{
    if (_start)
    {
        while (_finish != _start)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, _end_of_storage - _start);
    }
}

template<typename T>
void MyVector<T>::push_back(const T &val)
{
    if (_finish != _end_of_storage)
    {
        _alloc.construct(_finish++, val);
    }
    else
    {
        reallocate();
        _alloc.construct(_finish++, val);
    }
}

template<typename T>
void MyVector<T>::pop_back()
{
    if (_finish != _start)
    {
        _alloc.destroy(--_finish);
    }
}

template<typename T>
int MyVector<T>::size()
{
    return _finish - _start;
}

template<typename T>
int MyVector<T>::capacity()
{
    return _end_of_storage - _start;
}

template<typename T>
void MyVector<T>::reallocate()
{
    int old_size = size();
    int new_size = old_size ? 2 * old_size : 1;
    T *new_start = _alloc.allocate(new_size);
    T *new_finish = new_start;
    for (int i = 0; i < old_size; ++i)
    {
        _alloc.construct(new_finish++, _start[i]);
    }
    while (_finish != _start)
    {
        _alloc.destroy(--_finish);
    }
    if (_start)
    {
        _alloc.deallocate(_start, _end_of_storage - _start);
    }
    _start = new_start;
    _finish = new_finish;
    _end_of_storage = _start + new_size;
}

int main()
{
    MyVector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }
    cout << "size: " << vec.size() << endl;
    cout << "capacity: " << vec.capacity() << endl;
    for (int i = 0; i < 5; ++i)
    {
        cout << vec[i] << " ";
        vec.pop_back();
    }
    cout << endl;
    cout << "size: " << vec.size() << endl;
    cout << "capacity: " << vec.capacity() << endl;
    return 0;
}