#ifndef __CPPJIEBA_H__
#define __CPPJIEBA_H__

#include "Singleton.h"
#include "../src/offline/simhash/cppjieba/Jieba.hpp"

class Configuration;

class SplitToolCppJieba
:public Singleton<SplitToolCppJieba>
{
public:
    SplitToolCppJieba(Configuration * conf);
    ~SplitToolCppJieba();

    vector<string> cut(const string & sentence);
    void cutsmall(const string & sentence,vector<string> & deal,int);
private:
    Configuration * _conf;
    cppjieba::Jieba  _jieba;    
};


#endif
