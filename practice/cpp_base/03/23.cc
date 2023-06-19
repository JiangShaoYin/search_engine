#include <iostream>
using namespace std;

class Base{ 
	int a1,a2;
public:
	Base(int x1, int x2)
    :a1(x1),a2(x2)
    { }
    
    void print(){
        cout << a1 << endl;
        cout << a2 << endl;
    }
};

int main(){
	Base data(2,3);
 	data.print();
    return 0;
}