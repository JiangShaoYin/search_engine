#include "../../include/RssHeader.h"
/* #include "./simhash/Simhasher.hpp" */
#include "./simhash/Simhasher.hpp"

using namespace simhash;

RssReader::RssReader()
{
    
    
};



void RssReader::parseRss(const char * filename)
{
    cout<<"parseRss in"<<endl;
    XMLDocument xml;
    xml.LoadFile(filename);
    XMLElement *category = xml.RootElement();
    XMLElement *channel = category->FirstChildElement("channel");
    XMLElement *title = channel->FirstChildElement("title");
    XMLElement *item = channel->FirstChildElement("item");
    
    while (item)
    {
        
        RssItem rss_item;
        std::regex reg("<[^>]*>");
        XMLElement *item_title = item->FirstChildElement("title");
        if(item_title){
            rss_item.title = item_title->GetText();
            rss_item.title = regex_replace(rss_item.title,reg,"");
        }else{
            rss_item.title =" ";
        }
        //cout<<rss_item.title<<endl;
        
        XMLElement *item_link = item->FirstChildElement("link");
        if(item_link){
            rss_item.link = item_link->GetText();
        }else{
            rss_item.link=" ";
        }
        

        XMLElement *item_pubDate = item->FirstChildElement("pubDate");
        if(item_pubDate){
            rss_item.pubDate = item_pubDate->GetText();
        }else{
            rss_item.pubDate=" ";
        }
        

        XMLElement *item_author = item->FirstChildElement("author");
        if(item_author){
            rss_item.author = item_author->GetText();
        }else{
            rss_item.author=" ";
        }
        

        XMLElement *item_description = item->FirstChildElement("description");
        if(item_description){
            rss_item.description =item_description->GetText();
            rss_item.description = regex_replace(rss_item.description,reg,"");
        }else{
            rss_item.description=" ";
        }
        

        XMLElement *item_content = item->FirstChildElement("content");
        if(item_content){
            rss_item.content =item_description->GetText();
            rss_item.content = regex_replace(rss_item.content,reg,"");
        }else{
            rss_item.content=" ";
        }
        
        
        _rss.push_back(rss_item);
        
        item = item->NextSiblingElement();
        
    }
    cout<<"rss out"<<endl;
    
    


}

// 删除相似度较高的文章
void RssReader::deDuplicateBySimHash() {
    Simhasher simhasher("./dict/jieba.dict.utf8",
                         "./dict/hmm_model.utf8",
                         "./dict/idf.utf8", 
                         "./dict/stop_words.utf8");
    cout << "before simhash:" << _rss.size() << endl;

    vector<uint64_t> u64tmp;  // 暂存每篇文章的u64_t
    for (auto it = _rss.begin(); it != _rss.end(); ++it) {
        uint64_t currentHash;
        ::bzero(&currentHash, sizeof(uint64_t));

        string str_tocheck = (it->description) + (it->content);
        simhasher.make(
            str_tocheck,
            static_cast<size_t>(10),
            currentHash);
        u64tmp.push_back(currentHash);
    }

    std::vector<RssItem> last;  // 存放去重后的结果集合，会重新赋值给_rss
    last.push_back(_rss[0]);
    vector<uint64_t> saved_u64;
    saved_u64.push_back(u64tmp[0]);

    // 去重的循环
    cout << "u64:" << u64tmp.size() << endl;
    for (size_t i = 1; i < u64tmp.size() && i > saved_u64.size() - 1; ++i) {
        // 获取第i个文章，在前inputidx个中进行比对，若符合重复，则判断i的下一个，若不符合重复，则添加到last中。
        bool equal_flag = false;
        for (size_t j = 0; j < saved_u64.size(); ++j) {
            equal_flag = simhasher.isEqual(
                u64tmp[i], u64tmp[j],
                static_cast<unsigned short>(
                    10));
            // 符合重复，跳出本循环
            if (equal_flag == true)
                break;
        }
        // 符合重复-跳出上面的循环后，跳出本循环，进行i+1
        if (equal_flag) {
            continue;
        } else {
            // 不符合重复，添加simhash以及RssItem
            
            last.push_back(_rss[i]);
            saved_u64.push_back(u64tmp[i]);
        }
    }
    _rss = last;
    cout << "after simhash:" << _rss.size() << endl;
}




void RssReader::dump(vector<string> & _files,vector<string> & _noDocfiles,map<int,pair<int,int>> &_offsetLib){
        
    int fileid=1;
    int sizeSummary=0;
    for(auto rss:_rss){
        //cout <<"_files in in in!"<<endl;
        string  DocPage;
        string  noDocPage;
        DocPage ="<doc>" +string("<docid>")+to_string(fileid)+"</docid>"
                 +"<title>"+rss.title+"</title>"
                 +"<url>"+rss.link+"</url>"
                 +"<pubDate>"+rss.pubDate+"</pubDate>"
                 +"<author>"+rss.author+"</author>"
                 +"<description>"+rss.description+"</description>"
                 +"<content>"+rss.content+"</content>"+"</doc>";
        noDocPage =to_string(fileid)
                            +" "+rss.title
                            +" "+rss.link
                            +" "+rss.pubDate
                            +" "+rss.author
                            +" "+rss.description
                            +" "+rss.content+" ";
        //cout<<"u64:"<<u64<<endl;
        
        _files.push_back(DocPage);
        _offsetLib.insert(make_pair(fileid++,make_pair(sizeSummary,DocPage.size())));
        sizeSummary+=DocPage.size();
        _noDocfiles.push_back(noDocPage);
        
        
        
        
    }
    
}


