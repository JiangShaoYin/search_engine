#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class String {
public:
    String(){
        _pstr = new char[1];
    }
    String(const char * pstr){
        _pstr = new char[strlen(pstr) + 1];
        strcpy(_pstr, pstr);
    }
    String(const String & s){
        _pstr = new char[strlen(s._pstr) + 1];
        strcpy(_pstr, s._pstr);
    }
    ~String(){
        delete[] _pstr;
    }
    String &operator=(const String & s){
        delete[] _pstr;
        _pstr = new char[strlen(s._pstr) + 1];
        strcpy(_pstr, s._pstr);
        return *this;
    }
    String &operator=(const char * pstr){
        delete[] _pstr;
        _pstr = new char[strlen(pstr) + 1];
        strcpy(_pstr, pstr);
        return *this;
    }
    String &operator+=(const String & s){
        int lengh = strlen(_pstr) + strlen(s._pstr) + 1;
        char *temp = new char[lengh];
        strcpy(temp, _pstr);
        strcat(temp, s._pstr);
        delete[] _pstr;
        _pstr = temp;
    }
    String &operator+=(const char * pstr){
        int lengh = strlen(_pstr) + strlen(pstr) + 1;
        char *temp = new char[lengh];
        strcpy(temp, _pstr);
        strcat(temp, pstr);
        delete[] _pstr;
        _pstr = temp;
    }

    char &operator[](std::size_t index) {
        if (index >= strlen(_pstr)) {
            static char nullchar = '\0';
            return nullchar;
        }
        return _pstr[index];
    }
    const char &operator[](std::size_t index) const{
        if (index >= strlen(_pstr)) {
            static char nullchar = '\0';
            return nullchar;
        }
        return _pstr[index];
    }

    std::size_t size() const{
        return strlen(_pstr);
    }
    const char* c_str() const{
        char *res = new char[strlen(_pstr) + 1];
        strcpy(res, _pstr);
        return res;
    }

    friend bool operator==(const String & s1, const String & s2);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char * _pstr;
};

bool operator==(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) == 0;}
bool operator!=(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) != 0;}
bool operator<(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) < 0;}
bool operator>(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) > 0;}
bool operator<=(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) <= 0;}
bool operator>=(const String & s1, const String & s2){ return strcmp(s1.c_str(), s2.c_str()) >= 0;}

std::ostream &operator<<(std::ostream &os, const String &s){
    os << s.c_str();
    return os;
}
std::istream &operator>>(std::istream &is, String &s){
    vector<char> vec;
    char ch;
    ch = getchar();
    while (ch != '\n' && ch != ' ') {
        vec.push_back(ch);
        ch = getchar();
    }
    char *tmp = new char[vec.size() + 1];
    for (int i = 0; i < vec.size(); ++i) {
        tmp[i] = vec[i];
    }
    tmp[vec.size()] = '\0';
    s = tmp;
    return is;
}

String operator+(const String & s1, const String & s2){
    char * tmp = new char[s1.size()+ s2.size() + 1];
    strcpy(tmp, s1.c_str());
    strcat(tmp, s2.c_str());
    String s(tmp);
    return s;
}
String operator+(const String & s, const char * pstr){
    char * tmp = new char[s.size()+ strlen(pstr) + 1];
    strcpy(tmp, s.c_str());
    strcat(tmp, pstr);
    String res(tmp);
    return res;
}
String operator+(const char * pstr, const String & s){
    char * tmp = new char[strlen(pstr) + s.size() + 1];
    strcpy(tmp, pstr);
    strcat(tmp, s.c_str());
    String res(tmp);
    return res;
}

int main(){
    String s1("nihao");
    String s2("haha");
    //s1+=s2;
    //String s3 = s1;
    //cout << "s3 == s1? " << (s3 == s1) << endl;
    //s2 = s1;
    //cout << "s2 == s1? " << (s2 == s1) << endl;
    //cout << "s2 > s1? " << (s2 > s1) << endl;
    //cout << s1.c_str() << endl;

    //cout << "s1[0] = " << s1[0] << endl;
    //cout << s1 << endl;
    cin >> s1;
    //cout << s1 << endl;
    //s1[0] = 'a';
    //cout << s1 << endl;
    String res1 = s1 + s2;
    cout << res1 << endl;
    String res2 = res1 + "ceshi const char*";
    cout << res2 << endl;
    String res3 = "test const char *" + res2;
    cout << res3 << endl;

    return 0;
}
