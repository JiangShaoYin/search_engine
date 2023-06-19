#include "../../include/EngDictProducer.h"
#include "../../include/Configuration.h"
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <istream>

using std::ifstream;
using std::istringstream;
using std::regex;


EngDictProducer::EngDictProducer()
{
    //初始化文件绝对路径
    auto _conf= Configuration::GetInstance("");
    _dictfilepath = _conf->getConfigMap("data") + "/en_dictionary.dat";
    _indexfilepath = _conf->getConfigMap("data") + "/en_index_table.dat";
    string engFilePath = _conf->getConfigMap("english");
    DIR *dir;
    struct dirent *ent;
    dir = opendir(engFilePath.c_str());
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename != "." && filename != "..") {
                string temp = engFilePath + '/' + filename;
                _files.push_back(temp);
            }
        }
        closedir(dir);
    }
    //初始化停用词集
   stopwordlists = _conf->getEngStopWordList(); 

}

void EngDictProducer::buildDict()
{
    for (size_t i = 0;i < _files.size();++i)
    {
        ifstream ifs(_files[i]);
        string line;
        regex reg("[^a-zA-Z\\s]+");
        while (getline(ifs,line))
        {
            line = regex_replace(line, reg, " ");
            istringstream iss(line);
            string word;
            while (iss >> word)
            {
                for (auto & element : word){
                    element = tolower(element);
                }
                //deal with word
                if (stopwordlists.find(word) == stopwordlists.end()){
                    ++_dict[word];
                }
            }

        }
    }
}

void EngDictProducer::createIndex()
{
    _tofiledict = vector<pair<string,int>>(_dict.begin(),_dict.end());
    for (size_t i = 0;i < _tofiledict.size();++i)
    {
        for (auto & temp : _tofiledict[i].first){
            _index[temp].insert(i + 1);
        }
    }
}

void EngDictProducer::storeDict()
{
    std::ofstream ofsdict(_dictfilepath);
    for (auto & t : _tofiledict)
    {
        ofsdict << t.first << " " << t.second << std::endl;        
    }

    std::ofstream ofsindex(_indexfilepath);
    for (auto & t : _index)
    {
        ofsindex << t.first << " ";
        for (auto & tmp : t.second)
        {
            ofsindex << tmp << " ";
        }
        ofsindex << std::endl;
    }
}

void EngDictProducer::showFiles() const
{
    for (auto & temp : _index)
    {
        std::cout << temp.first << " ";
        for (auto & tmp : temp.second)
        {
            std::cout << tmp << " ";
        }
        std::cout << std::endl;
    }

}

void EngDictProducer::showDict() const
{
    for (auto & tmp : _dict)
    {
        std::cout << tmp.first << "-->" << tmp.second << std::endl;
    }

}
