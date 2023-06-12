#include "../../../include/Server_Thread.h"
#include <stdio.h>

__thread const char *name = "current_thread";

Thread::Thread(ThreadCallback &&cb, const string &name)
: _thid(0)
, _isRunning(false)
, _cb(std::move(cb))//回调函数的注册
, _name(name)
{

}

Thread::~Thread()
{

}

//线程运行函数
void Thread::start()
{
    //pthread_create函数的第三个参数，只能是void* ()(void *)
    //如果threadFunc是成员函数void *threadFunc(Thread *, void *)
    //所以将该函数设置为static
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        logError("Server_Thread::start()");
        return;
    }

    _isRunning = true;//线程在运行了
}

//线程退出函数
void Thread::join()
{
    if(_isRunning)
    {
        //查看系统函数的方法:shift + k(如果不在第一卷，加上卷数)(n + shift + k)
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join");
            logError("Server_Thread::join()");
            return;
        }
        _isRunning = false;
    }
}

//线程入口函数
void *Thread::threadFunc(void *arg)
{
    Thread *pth = static_cast<Thread *>(arg);
    name = pth->_name.c_str();//从string转换为const char *
    if(pth)
    {
        pth->_cb();//体现出来了多态
    }

    /* return nullptr; */
    pthread_exit(nullptr);
}


