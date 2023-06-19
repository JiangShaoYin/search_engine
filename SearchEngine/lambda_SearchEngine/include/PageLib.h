#ifndef __PAGELIB_H__
#define __PAGELIB_H__
#include <map>
#include <vector>
#include <string>
#include <utility>
#include "RssHeader.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cmath>

using std::map;
using std::vector;
using std::string;
using std::pair;

class PageLib{
public:
    PageLib();
    void create();
    void invertIndex();
    void store();
    
private:
    vector<string> _files;
    map<int,pair<int,int>> _offsetLib;
    vector<string> _noDocfiles;
    map<string,map<int,double>> _InvertIndexTable;
    RssReader rssReader;
    
};
#endif
