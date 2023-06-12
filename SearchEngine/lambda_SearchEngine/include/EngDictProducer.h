#ifndef __ENGDICTPRODUCER_H__
#define __ENGDICTPRODUCER_H__

#include <vector>
#include <utility>
#include <map>
#include <string>
#include <set>
#include "Configuration.h"
#include "DictProducer.h"

using std::string;
using std::vector;
using std::pair;
using std::map;
using std::set;

class EngDictProducer
:public DictProducer
{
public:
    EngDictProducer();
    ~EngDictProducer(){}

    //建立字典库
    void buildDict() override;

    //建立文件绝对路径_files
    void createIndex() override;
    //保存字典
    void storeDict() override;

    //test function
    void showFiles() const override;
    void showDict() const override;
private:
    vector<string> _files;//语料文件路径
    map<string,int>_dict;
    vector<pair<string,int>> _tofiledict;
    map<char,set<int>> _index;
    string _dictfilepath;//存放dat文件路径
    string _indexfilepath;//存放dat文件路径
    set<string> stopwordlists;
};


#endif

