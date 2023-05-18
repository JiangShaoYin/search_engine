#include <iostream>
#include <cstring>
using namespace std;

class String {
public:
    String()
        :_pstr(new char[1]) {cout << "String()" << endl;}
    String(const char * str)
        :_pstr(new char[strlen(str) + 1]) {
            cout << "String(char *)" << endl;
            strcpy(_pstr, str);
        }
    String(const String & rhs) 
        :_pstr(new char[strlen(rhs._pstr) + 1]) {
            cout << "String(const String &)" << endl;
            strcpy(_pstr, rhs._pstr);
        }
    // ref 
    String(String && ref)
        :_pstr(ref._pstr) {
            cout << "String(String &&)" << endl;
            ref._pstr = nullptr;
        }

    String & operator=(const String & rhs) {
        if(this != &rhs){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1];
            strcpy(_pstr, rhs._pstr);
        }
        cout << "String operator=(const String &)" << endl;
        return *this;
    }

    String &operator= (String && ref) {
        if(this != &ref){
            delete [] _pstr;
            _pstr = ref._pstr;
            ref._pstr = nullptr;
        }
        cout << "String operator=(String &&)" << endl;
        return *this;
    }

    char * cstr() const{
        return _pstr;
    }

    void print(){
        cout << _pstr << endl;
    }

private:
    char * _pstr;
};

int main() {
    String a = "hahaha";
    String b(a);
    String && ref = String("nihao");
    String c(move(ref));
    // 调用转移赋值函数
    c = move(a);
    c.print();
    return 0;
}
