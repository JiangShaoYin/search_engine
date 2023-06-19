#ifndef __TSINGLETON_H__
#define __TSINGLETON_H__

template <class T>
class Singleton
{
public:
    template <typename...Args>
    static T * getInstance(Args...args){
        if (pSingleton == nullptr){
            pSingleton = new T(args...);
        }
        return pSingleton;
    }

    static void destroy(){
        if (pSingleton){
            delete pSingleton;
        }
    }
private:
    Singleton(){}
    ~Singleton(){
    }
    static T * pSingleton;
};

template <class T>
T * Singleton<T>::pSingleton = nullptr;

#endif
