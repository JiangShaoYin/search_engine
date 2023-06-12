#ifndef __SPLITTOOL_H__
#define __SPLITTOOL_H__

#include <vector>
#include <string>

using std::string;
using std::vector;


class SplitTool
{
public:
    SplitTool(){};
    virtual ~SplitTool() = default;

    virtual vector<string> cut(const string & sentence) = 0;
    virtual void cutsmall(const string & sentence,vector<string> &,int) = 0;
};



#endif
