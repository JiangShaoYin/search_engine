#include "../../include/CppJieba.h"
#include "../../include/Configuration.h"

using cppjieba::Jieba;

SplitToolCppJieba::SplitToolCppJieba(Configuration * conf)
:_conf(conf)
,_jieba(_conf->getConfigMap("DICT_PATH"),
        _conf->getConfigMap("MODEL_PATH"),
        _conf->getConfigMap("USER_DICT_PATH"))
{
}

SplitToolCppJieba::~SplitToolCppJieba()
{
}

vector<string>  SplitToolCppJieba::cut(const string & sentence)
{
    vector<string> temp;
    _jieba.CutForSearch(sentence,temp);
    return temp;
}

void SplitToolCppJieba::cutsmall(const string & sentence,vector<string> & deal,int num)
{
    _jieba.CutSmall(sentence,deal,num);
}
