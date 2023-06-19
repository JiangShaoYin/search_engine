#include <iostream>
#include <vector>
using namespace std;

int main() {
    allocator<int> alloc;
    int *p = alloc.allocate(10);
    for (int i = 0; i < 10; ++i) {
        alloc.construct(p + i, i);
    }
    for (int i = 0; i < 10; ++i) {
        cout << p[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; ++i) {
        alloc.destroy(p + i);
    }
    alloc.deallocate(p, 10);
    return 0;
}