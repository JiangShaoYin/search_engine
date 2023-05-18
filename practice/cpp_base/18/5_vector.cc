#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;

template <class Container>
void display(const Container & t){
    for(auto & elem : t){
        cout << elem << " ";
    }
    cout << endl;
}
int main()
{
    cout << "vector constructor:" << endl;
    // 1 create empty instanse
    vector<int> v1;
    display(v1);
    // 2 assign count and value
    vector<int> v2(10,1);
    display(v2);
    // 3 using iterator
    int arr[] = {1, 2, 3, 4, 5};
    vector<int> v3(arr, arr + 5);
    display(v3);
    // 4 using another vector instance
    vector<int> v4(v2);
    display(v4);
    // 5 using {  }
    vector<int> v5 = {1, 2, 2, 3, 4, 5};
    display(v5);

    cout << endl << "list constructor:" << endl;
    // 1 create empty instanse
    list<int> l1;
    display(l1);
    // 2 assign count and value
    list<int> l2(10,1);
    display(l2);
    // 3 using iterator
    list<int> l3(arr, arr + 5);
    display(l3);
    // 4 using another list instance
    list<int> l4(l2);
    display(l4);
    // 5 using {  }
    list<int> l5 = {1, 2, 2, 3, 4, 5};
    display(l5);

    cout << endl << "deque constructor:" << endl;
    // 1 create empty instanse
    deque<int> d1;
    display(d1);
    // 2 assign count and value
    deque<int> d2(10,1);
    display(d2);
    // 3 using iterator
    deque<int> d3(arr, arr + 5);
    display(d3);
    // 4 using another deque instance
    deque<int> d4(d2);
    display(d4);
    // 5 using {  }
    deque<int> d5 = {1, 2, 2, 3, 4, 5};
    display(d5);
    
    return 0;
}

