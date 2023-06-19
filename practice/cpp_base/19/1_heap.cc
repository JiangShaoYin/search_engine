#include <iostream>
#include <vector>

using namespace std;

template <class T>
void swapVal(T & a, T & b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T, class Compare = std::less<T>>
class MyStackSort{
    public:
        MyStackSort(T * arr, int size, const Compare & com) 
        :_vec(vector<T>(arr, arr + size)){
            heapSort(size, com);
        }
        void adjustMaxHeap(int pos, int len, Compare & com);
        void heapSort(int size, Compare & com);
        void print() const {
            for(auto & elem : _vec) {
                cout << elem << " ";
            }
            cout << endl;
        }
    private:
        vector<T> _vec;
};

template<class T, class Compare >
void MyStackSort<T, Compare>::adjustMaxHeap(int pos, int len, Compare & com) {
    int dad = pos, son = dad * 2 + 1;
    while(son < len) {
        if(son + 1 < len && _vec[son + 1] > _vec[son]) {
            ++son;
        }
        if(_vec[son] > _vec[dad]) {
            swapVal(_vec[son], _vec[dad]);
            dad = son;
            son = dad * 2 + 1;
        }else{
            break;
        }
    }
}

template<class T, class Compare >
void MyStackSort<T, Compare>::heapSort(int size, Compare & com){
    // size是序号，i是下标，所以下标比序号小1，所以要-1
    for(int i = size / 2 - 1; i >= 0; --i) {
        adjustMaxHeap(i, size, com);
    }
    swapVal(_vec[0], _vec[size - 1]);
    for(int i = size - 1; i > 1; --i) {
        adjustMaxHeap(0, i, com);
        // i是位置，是数量，所以对应的下标是i - 1
        swapVal(_vec[0], _vec[i - 1]);
    }
}

int main(){
    int arr[] = {1,3,5,7,9,2,4,6,8,10};
    MyStackSort<int> m (arr, sizeof(arr) / sizeof(arr[0]), std::less<int>());
    m.print();
    return 0;
}

