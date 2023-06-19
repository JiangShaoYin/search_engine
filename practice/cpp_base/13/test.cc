#include <iostream>
using std::cout;
using std::endl;

class A {
public:
	virtual void a() {	cout << "a() in A" << endl;	}
	virtual void b() {	cout << "b() in A" << endl;	}
	virtual void c() {	cout << "c() in A" << endl;	}
};

class B : public A {
public:
    virtual void a() override {	cout << "a() in B" << endl;	}
    virtual void b() override {	cout << "b() in B" << endl;	}
    void c() {	cout << "c() in B" << endl;	}
};
class C : public B {
public:
    virtual void a() override {	cout << "a() in C" << endl;	}
    virtual void b() override {	cout << "b() in C" << endl;	}
    void c() {	cout << "c() in C" << endl;	}
};

int main(){
    C c;
    B *a = &c;
    a->c();
}