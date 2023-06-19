#pragma once
#include <memory>
#include <mutex>
#include <iostream>
using namespace std;
template <typename T>
class Singleton {
protected:
	Singleton() = default;
	Singleton(const Singleton<T>&) = delete;
	Singleton& operator=(const Singleton<T>& st) = delete;
	
	static std::shared_ptr<T> _instance;
public:
     template<typename... Args>
	static std::shared_ptr<T> GetInstance(Args&&... args) {
        if (_instance.get() == nullptr)
		    _instance = shared_ptr<T>(new T(std::forward<Args>(args)...));
		return _instance;
	}
	void PrintAddress() {
		std::cout << _instance.get() << endl;
	}
	~Singleton() {
		std::cout << "this is singleton destruct" << std::endl;
	}
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;
