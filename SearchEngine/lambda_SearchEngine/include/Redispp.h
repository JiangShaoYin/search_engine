#pragma once

#include <sw/redis++/redis++.h>
#include "Singleton.h"

using namespace sw::redis;

class Redispp
:public Singleton<Redis>
{
public:
    Redispp(const string & ip)
    :redispp(ip)
    {
    }

    Redispp()
    :redispp("tcp://127.0.0.1:6379")
    {

    }

    ~Redispp()
    {
    }

    Redis & getRedis()
    {
        return redispp;
    }

private:
    Redis redispp;
};

