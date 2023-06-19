#include "../../../include/CacheManager.h"

void CacheManager::init()
{
    _caches[0].readToFile(_filename);  
    for (size_t i = 0;i < _caches.size();++i)
    {
        _caches[i] = _caches[0];
    }
}

LRUCache & CacheManager::getCache(int num)
{
    return _caches[num];
}

void CacheManager::updateCache()
{   
    auto & mainCache = _caches[0];
    for (size_t i = 0;i < _caches.size();++i)
    {
        mypair temp;
        while ((temp = _caches[i].getpair()).first != "")
        {
            mainCache.putpair(temp);
            cout << temp.first << " " << temp.second << endl;
        }
    }
    //pending加载到主Cache中
    for (size_t i = 1;i < _caches.size();++i)
    {
        _caches[i] = mainCache;
    }
    //将主Cache覆盖至后续子Cache
    _caches[0].writeToFile(_filename);
}
