#pragma once

#include "Singleton.h"
#include "LRUCache.h"
#include "Configuration.h"
#include <vector>

using std::vector;

class CacheManager
:public Singleton<CacheManager>
{
public:
    CacheManager(Configuration * conf) 
    :_conf(conf)
    ,_filename(_conf->getConfigMap("LRUDUMP"))
    ,_cachenum(stoi(_conf->getConfigMap("THREADNUM")))
    ,_maxpending(stoi(_conf->getConfigMap("MAXPENDING")))
    {
        for (int i = 0;i < _cachenum;++i)
        {
            LRUCache lru(_maxpending);
            _caches.push_back(std::move(lru));
        }
//        init();
    }

    ~CacheManager() {}
    
    void init();

    LRUCache & getCache(int);

    void updateCache();


private:
    vector<LRUCache> _caches;    
    Configuration * _conf;
    string _filename;
    int _cachenum;
    int _maxpending;
};

