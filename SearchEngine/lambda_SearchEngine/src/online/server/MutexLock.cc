#include "../../../include/Server_MutexLock.h"
#include <stdio.h>

MutexLock::MutexLock()
{
    int ret = pthread_mutex_init(&_mutex, nullptr);
    if(ret)
    {
        perror("pthread_mutex_init");
        logError("Server_MutexLock::MutexLock()");
        return;
    }
}

MutexLock::~MutexLock()
{
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_destroy");
        logError("Server_MutexLock::~MutexLock()");
        return;
    }
}

//上锁
void MutexLock::lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_lock");
        logError("Server_MutexLock::lock()");
        return;
    }

}
void MutexLock::tryLock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_trylock");
        logError("Server_MutexLock::tryLock()");
        return;
    }

}
//解锁
void MutexLock::unlock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret)
    {
        perror("pthread_mutex_unlock");
        logError("Server_MutexLock::unLock()");
        return;
    }
}

