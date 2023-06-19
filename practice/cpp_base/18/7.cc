#include <iostream>
#include <vector>
using namespace std;

template<typename T,typename Compare=std::less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com){
        _vec = vector<T>(arr, arr + size);
        quick(0, size - 1, com);
    }   
    void quick(int left, int right, Compare &com);     
    int partition(int left, int right, Compare &com);     
    void print(); 
private:    
    vector<T> _vec; 
};

template<typename T,typename Compare>
void MyQsort<T,Compare>::print(){
    for(auto &e:_vec){
        cout << e << " ";
    }
    cout << endl;
}

template<typename T,typename Compare>
void MyQsort<T,Compare>::quick(int left, int right, Compare &com){
    if(left < right){
        int mid = partition(left, right, com);
        quick(left, mid - 1, com);
        quick(mid + 1, right, com);
    }
}

template<typename T,typename Compare>
int MyQsort<T,Compare>::partition(int left, int right, Compare &com){
    int i = left, j = left;
    for(i = left; i < right; ++i){
        if(com(_vec[i], _vec[right])){
            T tmp = _vec[i];
            _vec[i] = _vec[j];
            _vec[j] = tmp;
            ++j;
        }
    }
    T tmp = _vec[right];
    _vec[right] = _vec[j];
    _vec[j] = tmp;
    return j;
}

// 自定义比较函数
template<typename T>
class Comparator{
public:
    bool operator()(T a, T b){
        return a < b;
    }
};

int main(){
    int arr[] = {1, 3, 2, 5, 4};
    MyQsort<int, Comparator<int>> qsort(arr, 5, Comparator<int>());
    Comparator<int> com;
    qsort.quick(0, 4, com);
    qsort.print();
    return 0;
}