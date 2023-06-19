#include <vector>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <list>
#include <iostream> 

#define pendcap 4

using std::string;
using std::vector;
using std::make_pair;
using std::pair;
using std::unordered_map;
using std::list;
using std::cout;
using std::endl;

struct mypair
{
    string first;
    string second;
};



class LRUCache
{
public:
    LRUCache(int capacity)
    : _capacity(capacity)
    , _pendingcap(pendcap)
    {
    }

    string get(string query);

    int put(string query,string recommand);
    
    int writeToFile(const string &);

    int readToFile(const string &);

    void clear();
    
    void show();
    
    mypair getpair();
    
    void putpair(mypair temp);
    
    LRUCache & operator=(const LRUCache & other) {
        if (&other != this)
        {
            _cache = other._cache;
            _dlist = other._dlist;
        }
        return *this;
    }

public:
    list<pair<string,string>> _dlist;
    // list<pair<string,string>> _pendingUpdateList;
    unordered_map<string,pair<string,string>> _pendingUpdateList;
    unordered_map<string, list<pair<string,string>>::iterator> _cache;
    size_t _capacity;
    size_t _pendingcap;
};
