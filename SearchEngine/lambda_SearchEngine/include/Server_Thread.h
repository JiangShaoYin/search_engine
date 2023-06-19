#ifndef __THREAD_H__
#define __THREAD_H__

#include "log4pp.h"
#include <pthread.h>
#include <functional>

using std::function;
using std::bind;
using std::string;

extern __thread const char *name;

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&cb, const string &name = string());
    ~Thread();

    //线程运行函数
    void start();
    //线程退出函数
    void join();

private:
    //线程入口函数
    static void *threadFunc(void *arg);

private:
    pthread_t _thid;//线程id
    bool _isRunning;//线程是否运行的标志
    ThreadCallback _cb;//存任务的
    string _name;//线程名字

};

#endif

