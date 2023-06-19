#include "../../include/Configuration.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

Configuration::Configuration(const string & filepath)
:_filepath(filepath)    
{
    ifstream ifs(_filepath);
    string line;
    while (getline(ifs,line)){
        string word;
        size_t found = line.find_first_of(" ");
        word = line.substr(0,found);
        line = line.substr(found + 1,line.size());
        _configMap[word] = line; // add map
    }
    //engstopwordlist
    string stopWordPath = _configMap["engstopword"];
    ifstream ifsstopeng(stopWordPath);
    while (getline(ifsstopeng,line)){
        istringstream iss(line);
        string word;
        iss >> word;
        _engStopWordList.insert(word);
    }        

    //_cnStopWordList
    stopWordPath = _configMap["zhstopword"];
    ifstream ifsstopcn(stopWordPath);
    while (getline(ifsstopcn,line)){
        istringstream iss(line);
        string word;
        iss >> word;
        _cnStopWordList.insert(word);
    }        
}

string Configuration::getConfigMap(const string & key)
{
    return _configMap[key];
}

set<string> Configuration::getEngStopWordList()
{
    return _engStopWordList;
}

set<string> Configuration::getCnStopWordList()
{
    return _cnStopWordList;
}

void Configuration::show()
{
    cout << "-------------------------------" << endl;
    cout << "filepath = " << _filepath << endl;
    cout << "-------------------------------" << endl;
    for (auto & tmp : _configMap)
    {
        cout << tmp.first << "-->" << tmp.second << endl; 
    }
    cout << "-------------------------------" << endl;
    for (auto & tmp : _cnStopWordList)
    {
        cout << tmp << endl;
    }
    cout << "-------------------------------" << endl;
}
