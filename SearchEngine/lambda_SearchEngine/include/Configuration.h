#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <set>
#include <map>
#include <string>
#include "Singleton.h"

using std::set;
using std::map;
using std::string;

class Configuration
:public Singleton<Configuration>
{
public:
    Configuration(const string & filepath);
    Configuration(){};
    ~Configuration(){}
    string getConfigMap(const string &);
    set<string> getEngStopWordList();
    set<string> getCnStopWordList();

    void show();
private:
    string _filepath;
    map<string,string> _configMap;
    set<string> _engStopWordList;
    set<string> _cnStopWordList;
};




#endif

