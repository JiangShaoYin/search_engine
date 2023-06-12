#include "../../../include/Server_MutexLock.h"
#include "../../../include/Server_Condition.h"
#include <stdio.h>
    
Condition::Condition(MutexLock &mutex)
: _mutex(mutex)
{
    int ret = pthread_cond_init(&_cond, nullptr);
    if(ret)
    {
        perror("pthread_cond_init");
        logError("Server_Condition::Condition()");
        return;
    }
}

Condition::~Condition()
{
    int ret = pthread_cond_destroy(&_cond);
    if(ret)
    {
        perror("pthread_cond_destroy");
        logError("Server_Condition::~Condition()");
        return;
    }
}

void Condition::wait()
{
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
    if(ret)
    {
        perror("pthread_cond_wait");
        logError("Server_Condition::wait()");
        return;
    }

}
void Condition::notify()
{
    int ret = pthread_cond_signal(&_cond);
    if(ret)
    {
        perror("pthread_cond_signal");
        logError("Server_Condition::notify()");
        return;
    }

}
void Condition::notifyAll()
{
    int ret = pthread_cond_broadcast(&_cond);
    if(ret)
    {
        perror("pthread_cond_broadcast");
        logError("Server_Condition::notifyAll()");
        return;
    }

}

