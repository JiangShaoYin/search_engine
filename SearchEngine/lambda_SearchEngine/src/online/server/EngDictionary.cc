#include "../../../include/EngDictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

EngDictionary::EngDictionary(const string & dictpath)
{
    _dictpath = dictpath + "/en_dictionary.dat";
    _indexpath = dictpath + "/en_index_table.dat";
}

EngDictionary::~EngDictionary()
{
    
}

void EngDictionary::init()
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

pair<string,int>  EngDictionary::getDict(size_t num)
{
    return _dict[num - 1];
}

set<int> EngDictionary::getIndex(const string & word)
{
    return _index[word];
}

void EngDictionary::show()
{
    for (auto & t : _index)
    {
        cout << t.first << " ";
        for (auto & tt : t.second)
        {
            cout << tt << " ";                
        }
        cout << endl;
    }
}
