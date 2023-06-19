#ifndef __CNDICTPRODUCER_H__
#define __CNDICTPRODUCER_H__

#include <vector>
#include <utility>
#include <map>
#include <string>
#include <set>
#include "DictProducer.h"
#include "CppJieba.h"

using std::string;
using std::vector;
using std::pair;
using std::map;
using std::set;

class CnDictProducer
:public DictProducer
{
public:
    CnDictProducer(SplitToolCppJieba * _cuttor);
    ~CnDictProducer(){}

    //建立字典库
    void buildDict() override;

    //建立文件绝对路径_files
    void createIndex() override;
    //保存字典
    void storeDict() override;
    //是否中文
    bool isChinese(const string & word);
    //test function
    void showFiles() const override;
    void showDict() const override;
private:
    vector<string> _files;//语料文件路径
    map<string,int>_dict;
    map<string,set<int>> _index;
    SplitToolCppJieba *  _cuttor;    
    string _dictfilepath;
    string _indexfilepath;
    set<string> stopwordlists;
};


#endif

