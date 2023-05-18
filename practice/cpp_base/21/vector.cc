#include <iostream>
#include <memory>
using std::cout;
using std::endl;

template<typename T>
class Vector
{
public:
    Vector() {
        _start = _finish = _end_of_storage = nullptr;
    }
    ~Vector() {
        if(_start) {
            while(_start != _finish) {
                _alloc.destroy(_finish);
                --_finish;
            }
            _alloc.deallocate(_start, _end_of_storage - _start);
        }
    }
    void push_back(const T & val) {
        if(_finish != _end_of_storage) {
            _alloc.construct(_finish, val);
            ++_finish;
        }else {
            reallocate();
            _alloc.construct(_finish, val);
            ++_finish;
        }
    }
    void pop_back() {
        if(_start != _finish) {
            _alloc.destroy(--_finish);
        }else {
            cout << "the vector is empty" << endl;
        }
    }
    int size() {
        return _finish - _start;
    }
    int capacity() {
        return _end_of_storage - _start;
    }
private:
    void reallocate() {//重新分配内存,动态扩容要用的
        int oldSize = size();
        int newSize = oldSize? 2 * oldSize : 1;
        T * newStart = _alloc.allocate(newSize);
        T * newEndOfStorage = newStart + newSize;
        T *newEnd = newStart;
        T * temp = _start;
        for(;temp != _finish; ++temp) {
            *newEnd = *temp;
            ++newEnd;
        }
        while(_finish != _start) {
            _alloc.destroy(--_finish);
        }
        if(_start)
            _alloc.deallocate(_start, _end_of_storage - _start);
        _start = newStart;
        _finish = newEnd;
        _end_of_storage = newEndOfStorage;
    }
private:
    static std::allocator<T> _alloc;
    T *_start;                 //指向数组中的第一个元素
    T *_finish;                //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};


template<typename T>
std::allocator<T> Vector<T>::_alloc;

int main()
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(5);
    return 0;
}

