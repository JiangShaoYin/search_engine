#pragma once
#include <iostream>
#include <regex>
#include <fstream>
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <map>
#include <utility>
#define LOGGER_LEVEL LL_WARN 



using std::string;
using namespace tinyxml2;
using std::map;
using std::vector;
using std::pair;
using std::cout;
using std::endl;
using std::to_string;

struct RssItem {
    string title;
    string link;
    string pubDate;
    string author;
    string description;
    string content;
    
};
   
class RssReader{
public:
    RssReader();

    void parseRss(const char *filename);//解析
    
    void deDuplicateBySimHash();
    
    void dump(vector<string> & _files,vector<string> & _noDocfiles,map<int,pair<int,int>> &_offsetLib);//输出

private:
    vector<RssItem> _rss;
    
}; 
