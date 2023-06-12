#include "../../include/CnDictProducer.h"
#include "../../include/Configuration.h"
#include <dirent.h>
#include <iostream>
#include <fstream>


using std::ifstream;

CnDictProducer::CnDictProducer(SplitToolCppJieba * cuttor)
:_cuttor(cuttor)
{
    //初始化文件绝对路径
    auto _conf = Configuration::GetInstance("");
    _dictfilepath = _conf->getConfigMap("data") + "/cn_dictionary.dat";
    _indexfilepath = _conf->getConfigMap("data") + "/cn_index_table.dat";
    string cnFilePath = _conf->getConfigMap("chinese");
    DIR *dir;
    struct dirent *ent;
    dir = opendir(cnFilePath.c_str());
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename != "." && filename != "..") {
                string temp = cnFilePath + '/' + filename;
                _files.push_back(temp);
            }
        }
        closedir(dir);
    }

    //初始化停用词集
    stopwordlists = _conf->getCnStopWordList(); 
}

void CnDictProducer::buildDict()
{
    for (size_t i = 0;i < _files.size();++i)
    {
        ifstream ifs(_files[i]);
        string line;
        while (getline(ifs,line)){
            vector<string> words;
            vector<string> cnword;
            words = _cuttor->cut(line);
            for (size_t j = 0;j < words.size();++j)
            {
                string temp = words[j];
                if (stopwordlists.find(temp) == stopwordlists.end() && 
                    isChinese(temp)){
                    _dict[temp]++;
                }
            }
        }
    }
}

void CnDictProducer::createIndex()
{
    int i = 1;
    for (auto & t : _dict)
    {
        vector<string> temp;
        _cuttor->cutsmall(t.first,temp,1);
        for (auto & temp : temp){
            _index[temp].insert(i);
        }
        ++i;
    }

}

void CnDictProducer::storeDict()
{   /* {    std::ofstream ofsdict(_dictfilepath); */
    std::ofstream ofsdict;
    ofsdict.open(_dictfilepath);
    for (auto & t : _dict)
    {
        ofsdict << t.first << " " << t.second << std::endl;        
    }

    /* std::ofstream ofsindex(_indexfilepath); */
    std::ofstream ofsindex;
    ofsindex.open(_indexfilepath);
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

void CnDictProducer::showFiles() const
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

void CnDictProducer::showDict() const
{
    for (auto & tmp : _dict)
    {
        std::cout << tmp.first << "-->" << tmp.second << std::endl;
    }

}

bool CnDictProducer::isChinese(const string &str)
{

    for (size_t i = 0; i < str.length(); i++)
    {
        if ((str[i] & 0xE0) == 0xE0 && i + 2 < str.length())
        {
            unsigned int c = ((unsigned int)str[i] & 0x0F) << 12 |
                ((unsigned int)str[i + 1] & 0x3F) << 6 |
                ((unsigned int)str[i + 2] & 0x3F);
            if (c >= 0x4E00 && c <= 0x9FFF)
            {
                return true;
            }
            i += 2;
        }
    }
    return false;
}




