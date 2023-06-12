#include "../../../include/CnDictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

CnDictionary::CnDictionary(const string & dictpath)
{
    _dictpath = dictpath + "/cn_dictionary.dat";
    _indexpath = dictpath + "/cn_index_table.dat";
}

CnDictionary::~CnDictionary()
{
    
}

void CnDictionary::init()
{
    //初始化词典
    ifstream ifsdict(_dictpath);
    string line;
    string word;
    int frequency;
    while (getline(ifsdict,line))
    {
        istringstream iss(line);
        iss >> word >> frequency;
        _dict.push_back(make_pair(word,frequency));
    }
    //初始化索引
    int index;
    ifstream ifsindex(_indexpath);
    while (getline(ifsindex,line))
    {
        istringstream iss(line);
        iss >> word;
        while (iss >> index)
        {
            _index[word].insert(index);
        }
    }
}

pair<string,int>  CnDictionary::getDict(size_t num)
{
    return _dict[num - 1];
}

set<int> CnDictionary::getIndex(const string & word)
{
    return _index[word];
}

void CnDictionary::show(const string & word)
{
    set<int> temp = _index[word];
    for (auto & t : temp)
    {
        cout << t << endl;
    }
}

