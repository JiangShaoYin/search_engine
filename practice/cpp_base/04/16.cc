#include <iostream>
#include <cstring>
using namespace std;

class String
{
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};
String::String(){
    cout << "String()" << endl;
    _pstr = new char[1];
}
String::String(const char *pstr){
    cout << "String(const char *pstr)" << endl;
    _pstr = new char[strlen(pstr) + 1];
    strcpy(_pstr, pstr);
}
String::String(const String &rhs){
    cout << "String(const String &rhd)" << endl;
    _pstr = new char[strlen(rhs._pstr) + 1];
    strcpy(_pstr, rhs._pstr);
}
String& String::operator=(const String &rhs){
    cout << "String& operator=(const String &rhs)" << endl;
    if(this != &rhs){
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr) + 1];
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}
String::~String() {
    cout << "~String()" << endl;
    delete [] _pstr;
}
void String::print() {
    cout << "print()" << endl;
    printf("%s\n", _pstr);
}
size_t String::length() const {
    return strlen(_pstr);
}
const char * String::c_str() const {
    return _pstr;
}

int main()
{
	String str1;
	str1.print();
	

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}
