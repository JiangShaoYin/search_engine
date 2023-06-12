#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include <vector>
#include <utility>
#include <map>
#include <string>
#include <set>
#include "SplitTool.h"
#include "Configuration.h"

using std::string;
using std::vector;
using std::pair;
using std::map;
using std::set;

class DictProducer
{
public:
    DictProducer(){}    
    virtual ~DictProducer(){}

    //建立字典库
    virtual void buildDict() = 0;

    //建立文件绝对路径_files
    virtual void createIndex() = 0;
    virtual void storeDict() = 0;

    //test function
    virtual void showFiles() const = 0;
    virtual void showDict() const = 0;
};


#endif
