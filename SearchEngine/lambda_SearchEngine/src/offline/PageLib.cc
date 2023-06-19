#include "../../include/PageLib.h"
#include "../../include/Configuration.h"
#include "../../include/CppJieba.h"

PageLib::PageLib()
:_files()
,_offsetLib()
,_noDocfiles()
,_InvertIndexTable()
,rssReader()
{
}

void PageLib::create(){
    auto _conf = Configuration::GetInstance("");
    string pageFilePath = _conf->getConfigMap("pageSource");
    DIR *dir;
    struct dirent *ent;
    dir = opendir(pageFilePath.c_str());
    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            string filename = ent->d_name;
            if (filename != "." && filename != "..") {
                string temp = pageFilePath + '/' + filename;
                std::cout << temp << std::endl;
                rssReader.parseRss(temp.c_str());                
                        
            }

        }
        
        closedir(dir);
    }
    cout<<"jiexi"<<endl;
    rssReader.deDuplicateBySimHash();
    
    cout<<"parseRss finish!"<<endl;
    rssReader.dump(_files,_noDocfiles,_offsetLib);
    
    cout << "_files.size() = " << _files.size() << endl;

}

//vector<string> _noDocfiles  不含doc的网页库
//
void PageLib::invertIndex(){
    map<string,map<int,int>> DfTabel;
    map<int,map<string,double>>FiletoW;
    auto _jieba = SplitToolCppJieba::GetInstance(Configuration::GetInstance("").get());     
    for(size_t fileid=1;fileid<_noDocfiles.size()+1;++fileid){
        vector<string> wordtemp =_jieba->cut(_noDocfiles[fileid-1]);
        for(auto str:wordtemp){
            auto DfTemp=DfTabel.find(str);
            if(DfTemp==DfTabel.end()){
                map<int,int> singleWoTemp;
                singleWoTemp.insert(std::make_pair(fileid,1));
                DfTabel.insert(std::make_pair(str,singleWoTemp));
                continue;
            }
            auto & DfTemp2=DfTemp->second;
            if(DfTemp2.find(fileid)==DfTemp2.end()){
                DfTemp2.insert(std::make_pair(fileid,1));
                continue;
            }
            ++DfTemp2.find(fileid)->second;
        }

    }
    
    
    /*
    for(auto it=DfTabel.begin();it!=DfTabel.end();++it){
        string word = it->first;  // 获得键
        cout<< word<< "   ";
        map<int, int> value = it->second; // 获得值
        for(auto val:value){
            cout<<val.first<<"  "
                <<val.second<<"  ";    
        }
        cout<<endl;  
    }
    */
    size_t N=_noDocfiles.size();
    for(auto stemp:DfTabel){
        size_t DF=stemp.second.size();
        for(auto stemp2: stemp.second){
            size_t TF=stemp2.second;
            double IDF=std::log2(N/DF+1);
            double w=TF*IDF;
            auto FW=FiletoW.find(stemp2.first);
            if(FW==FiletoW.end()){
                FiletoW.insert(std::make_pair(stemp2.first,map<string,double>{{stemp.first,w}}));
                continue;
            }
            FW->second.insert(std::make_pair(stemp.first,w));
        }
    }
    for(auto stemp:DfTabel){
        map<int,double> wIndex;
        for(auto stemp2: stemp.second){
            double w=0;
            double wSum=0;
            auto FW=FiletoW.find(stemp2.first);
            for(auto wset:FW->second){
                if(wset.first==stemp.first){
                    w=wset.second;
                }
                wSum+=std::pow(wset.second,2);
            }
            double wResult=w/std::sqrt(wSum);
            wIndex.insert(std::make_pair(stemp2.first,wResult));
        }
        _InvertIndexTable.insert(std::make_pair(stemp.first,wIndex));
    }
    
    
    
}




void PageLib::store(){
    
    std::ofstream ofspage("../../data/pagetest.dat");

    if (!ofspage.good())
    {
        std::cerr << "ofstream is corrupted!" << endl;
        return;
    }
    cout << "_files.size() = " << _files.size() << endl;
    for (size_t i = 0;i < _files.size(); ++i)
    {
        ofspage <<_files[i]; 
    }

    ofspage.close();
    
    std::ofstream ofsoffset("../../data/offsettest.dat");

    if (!ofsoffset.good())
    {
        std::cerr << "ofstream is corrupted!" << endl;
        return;
    }
    cout << "_files.size() = " << _offsetLib.size() << endl;
    for (auto it = _offsetLib.begin(); it != _offsetLib.end(); ++it) {
        int id = it->first;  // 获得键
        pair<int, int> value = it->second; // 获得值
        int a = value.first; 
        int b = value.second;
        ofsoffset << id << " " << a << " " << b << " " << endl;
    }
    ofsoffset.close();
    
    std::ofstream ofsInvert("../../data/Inverttest.dat");

    if (!ofsInvert.good())
    {
        std::cerr << "ofstream is corrupted!" << endl;
        return;
    }
    cout << "_files.size() = " << _offsetLib.size() << endl;
    for(auto it=_InvertIndexTable.begin();it!=_InvertIndexTable.end();++it){
        string word = it->first;  // 获得键
        ofsInvert<< word<< "   ";
        map<int, double> value = it->second; // 获得值
        for(auto val:value){
            ofsInvert<<val.first<<"  "
                <<val.second<<"  ";    
        }
        ofsInvert<<endl;  
    }
    ofsInvert.close();
    
    
    

}

