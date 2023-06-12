#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include<vector>
#include<map>
#include<utility>
#include<string>
#include<set>

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::set;

class Dictionary
{
public:
    virtual void init() = 0;

    virtual pair<string,int> getDict(size_t num)= 0;

    virtual set<int> getIndex(const string &) = 0;
};

#endif
