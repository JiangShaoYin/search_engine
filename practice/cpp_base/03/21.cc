#include <iostream>
using namespace std;

int i = 1;

class Test{
public:
	Test()
	:_fourth(_third),_second(i++),_first(i++),_third(i++){
		_third = i;
	}
	void print(){  
        cout << "first : " << _first << endl;
        cout << "second : " << _second << endl;
        cout << "third : " << _third << endl;
        cout << "fourth : " << _fourth << endl;
		cout << "result : " << _first + _second + _third + _fourth << endl;
	}
private:
	int _first;
	int _second;
	int _third;
	int &_fourth;
};

int main(){
	Test test;
	test.print();
	
	return 0;
}