#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <list>
#include <functional>
using namespace std;
void test0() {
    vector<int> vec{1, 2, 3, 4, 5};
    list<int> lst;
    copy(vec.begin(), vec.end(), back_inserter(lst));
    copy(vec.begin(), vec.end(), front_insert_iterator<list<int>>(lst));
    copy(lst.begin(), lst.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void test1() {
    vector<int> vec{1, 2, 3, 4, 5};
    reverse_iterator<vector<int>::iterator> rit = vec.rbegin();
    for(; rit != vec.rend(); ++rit) {
        cout << *rit << " ";
    }
}

int fuc(int a, int b, int c) {
    return a + b + c;
}

void test2() {
    function<int()> f = bind(fuc, 1, 2, 3);
    cout << "f() = " << f() << endl;

    function<int(int,int)> f1 = bind(fuc, placeholders::_2, 99, 88);
    cout << "f1(1) = " << f1(1,2) << endl;
}

void print(int i) {
    cout << i << " ";
}

void test3(){
    vector<int> vec{1, 2, 3, 4, 5};
    int a = 11;
    for_each(vec.begin(), vec.end(), [&a](int i) {cout << a++ << "-" << i << " ";});
    // for_each(vec.begin(), vec.end(), &print);
}

bool isEven(int i) {
    return i % 2 == 0;
}

void test4() {
    vector<int> vec{1, 2, 3, 4, 5};
    cout << count_if(vec.begin(), vec.end(), [](int i){
        return i % 2 != 0;
    }) << endl;
}

int main() {
    test4();
    return 0;
}