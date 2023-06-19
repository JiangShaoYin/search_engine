#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
class CharProxy {
public:
    CharProxy(int idx, T* pCowString)
    :_idx(idx)
    ,_pCowString(pCowString) {}
    
    // 读操作 输出运算符重载
    friend ostream & operator<<(ostream & os, const CharProxy & rhs){
        if(rhs._idx >= 0 && rhs._idx < strlen(rhs._pCowString->cStr())){
            os << rhs._pCowString->cStr()[rhs._idx];
        }else{
            cout << "下标越界" << endl;
        }
        return os;
    }
    // 写操作 赋值运算符重载
    CharProxy & operator=(const char & rhs){
        if(_idx >= 0 && _idx < strlen(_pCowString->cStr())){
            if(*(int*)(_pCowString->cStr() - 4) > 1){ // 引用计数大于1，深拷贝
                // 现将原来的引用计数减1，然后深拷贝，再将引用计数置为1
                _pCowString->decreaseRefCount();
                char * ptmp = new char[_pCowString->size() + 5] + 4;
                strcpy(ptmp, _pCowString->cStr());
                _pCowString->_pstr = ptmp;
                _pCowString->initRefCount();
            }
            _pCowString->cStr()[_idx] = rhs;
        }
        else{
            cout << "下标越界" << endl;
        }
        return *this;
    }
    
private:
    int _idx;
    T* _pCowString;
};

class CowString {
public:   // 构造函数
    CowString()
    :_pstr(new char[5] + 4)
    ,_pProx(0, this){
        initRefCount();
    }
    CowString(const char* pstr)
    :_pstr(new char[strlen(pstr) + 5] + 4)
    ,_pProx(0, this){
        initRefCount();
        strcpy(_pstr, pstr);
    }
    CowString(const CowString & rhs)
    :_pstr(rhs._pstr)
    ,_pProx(rhs._pProx) { //  浅拷贝
        initRefCount();
    }
    // 析构函数
    ~CowString(){ release(); }
    // 其他函数
    int size() const { return strlen(_pstr); }
    char * cStr() const { return _pstr; }
    int getRefCount(){ return *(int*)(_pstr - 4); }
    // 运算符重载函数
    CowString & operator=(const CowString & rhs) {
        if(this != &rhs) {
            release();
            _pstr = rhs._pstr; // 浅拷贝
            increaseRefCount();
        }
        return *this;
    } 

    friend ostream & operator<<(ostream & os, const CowString & rhs);
    friend class CharProxy<CowString>;

    CharProxy<CowString> & operator[](int index){
        if(index >= 0 && index < size()){
            _pProx = CharProxy<CowString>(index, this);
            return _pProx;
        }
        else{
            cout << "下标越界" << endl;
            static CowString s;
            static CharProxy<CowString> nullchar(0, &s);
            return nullchar;
        }
    }

private:
    void initRefCount(){
        *(int*)(_pstr - 4) = 1;
    }
    void release(){
        decreaseRefCount();
        if(*(int*)(_pstr - 4) == 0){
            delete[] (_pstr - 4);
            cout << "release" << endl;
        }
    }
    void increaseRefCount(){
        ++*(int*)(_pstr - 4);
    }
    void decreaseRefCount(){
        --*(int*)(_pstr - 4);
    }
private:
    char * _pstr;
    CharProxy<CowString> _pProx;
};

ostream & operator<<(ostream & os, const CowString & rhs){
    os << rhs._pstr;
    return os;
}

int main() {
    CowString s1 = "hello";
    CowString s2 = s1;
    printf("s1 = %p\n", s1.cStr());
    printf("s2 = %p\n", s2.cStr());
    cout << "s1: " << s1 << endl;
    cout << "s2[0]: " << s2[0] << endl;
    s2[0] = 'H';
    cout << "s2[0]: " << s2[0] << endl;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    return 0;
}

