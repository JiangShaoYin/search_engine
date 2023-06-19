#ifndef __CNDICTIONARY_H__
#define __CNDICTIONARY_H__

#include "Dictionary.h"


class CnDictionary
:public Dictionary
{
public:
    CnDictionary(const string & dictpath);
    ~CnDictionary();
    void init();

    pair<string,int> getDict(size_t num);
    set<int> getIndex(const string &);

    void show(const string &);
private:
    vector<pair<string,int>> _dict;
    map<string,set<int>>  _index;
    string _dictpath;
    string _indexpath;
};






#endif
