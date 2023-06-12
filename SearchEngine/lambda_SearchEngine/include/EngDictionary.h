#ifndef __ENGDICTIONARY_H__
#define __ENGDICTIONARY_H__

#include "Dictionary.h"


class EngDictionary
:public Dictionary
{
public:
    pair<string,int>  getDict(size_t num);
    set<int> getIndex(const string &);

    EngDictionary(const string & dictpath);
    ~EngDictionary();
    void init();
    void show();
private:
    vector<pair<string,int>> _dict;
    map<string,set<int>>  _index;
    string _dictpath;
    string _indexpath;
};












#endif
