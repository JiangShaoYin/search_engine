#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main(){
    vector<int> c1 = {1, 3, 5, 7, 9};
    vector<int> c2 = {1, 2, 4, 6, 8};
    // deque<int> c2 = {1, 2, 4, 6, 8};
    // vector<double> c2 = {1, 2, 4, 6, 8};
    cout << "test: " << (c1 < c2) << endl;
    cout << "test: " << (c1 > c2) << endl;
    // 容器比较的限制为：两个容器的类型必须相同，且元素类型也必须相同
    return 0;
}

