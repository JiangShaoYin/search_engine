#include <iostream>
#include <vector>
using namespace std;

template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com)
        :_vec(vector<T>(arr, arr + size)){
            quick(0, size - 1, com);
        }     
    void quick(int left, int right, const Compare &com);     
    int partition(int left, int right, const Compare &com);     
    void print();
private:    
    vector<T> _vec; 
};

template<typename T>
class Comparator{
public:
    bool operator()(T a, T b) const {
        return a < b;
    }
};

template<typename T,typename Compare> 
void MyQsort<T,Compare>::quick(int left, int right, const Compare & com) {
    if(left < right) {
        int mid = partition(left, right, com);
        quick(left, mid - 1, com);
        quick(mid + 1, right, com);
    }
}

template<typename T,typename Compare> 
int MyQsort<T,Compare>::partition(int left, int right, const Compare &com) {
    int i = left, j = left;
    for(i = left; i < right; ++i){
        if(com(_vec[i], _vec[right])){
            T tmp = _vec[j];
            _vec[j] = _vec[i];
            _vec[i] = tmp;
            ++j;
        }
    }
    T tmp = _vec[right];
    _vec[right] = _vec[j];
    _vec[j] = tmp;
    return j;
}

template<typename T,typename Compare> 
void MyQsort<T,Compare>::print(){
    for(auto & elem : _vec){
        cout << elem << " ";
    }
    cout << endl;
}

int main(){
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8};
    // 参数需要的是一个对象，所以需要加上括号
    // 尖括号中因为有默认参数，所以可以不传
    MyQsort<int> qsort(arr, sizeof(arr) / sizeof(arr[0]), std::less<int>());
    qsort.print();
    int arr2[] = {1,4,6,8,2,4,5,8,0};
    // 因为没有用到默认参数，尖括号要传入两个参数
    MyQsort<int, Comparator<int>> my (arr2, sizeof(arr2) / sizeof(arr2[0]), Comparator<int>());
    
    my.print();
    return 0;
}

