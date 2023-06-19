#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <list>
#include <map>

using namespace std;

/*
分别给出最适合使用list、vector、deque、map以及set的例子
*/

template<class T>
void display(const T & t) {
    for(auto & elem : t) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    // list 适合在任意位置插入元素操作较多时使用
    list<int> l;
    l.push_back(1);
    l.push_front(2);
    l.insert(l.begin(), 3);
    l.insert(l.end(), 4);
    cout << "list:";
    display(l);
    // vector适合频繁访问元素或者尾部增加和删除元素的场景。
    vector<int> v;
    v.push_back(1);
    cout << "vector:";
    display(v);
    // deque双端队列，适合频繁在头尾插入删除元素的场景。
    deque<int> d;
    d.push_back(1);
    d.push_front(2);
    d.insert(d.begin(), 3);
    d.insert(d.end(), 4);
    cout << "deque:";
    display(d);
    // map需要按某个特征进行访问的场景
    map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    cout << "map:";
    for(auto & elem : m) {
        cout << elem.first << " " << elem.second << endl;
    }
    // set适合顺序储存，且不要重复值的场景
    set<int> s;
    s.insert(1);
    s.insert(3);
    s.insert(2);
    s.insert(3);
    cout << "set:";
    display(s);
}