#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include"tinyxml2.h"

using namespace tinyxml2;
using namespace std;


struct RssItem {
    string title;
    string link;
    string description;
    string content;
};
   
class RssReader{
public:
    RssReader(){
        cout << "RssReader()" << endl;
    }
    //解析
    void parseRss(){
        XMLDocument doc;
        doc.LoadFile("coolshell.xml");
        XMLElement * root = doc.RootElement();
        XMLElement * channel = root->FirstChildElement("channel");
        XMLElement * item = channel->FirstChildElement("item");
        while(item){
            RssItem rss;
            XMLElement * title = item->FirstChildElement("title");
            XMLElement * link = item->FirstChildElement("link");
            XMLElement * description = item->FirstChildElement("description");
            XMLElement * content = item->FirstChildElement("content:encoded");
            rss.title = title->GetText();
            rss.link = link->GetText();
            // 使用std::regex正则表达式过滤掉html标签
            string pattern = "<[^>]*>";
            regex r(pattern);
            // 换行符一起过滤掉
            string pattern2 = "\n";
            regex r2(pattern2);
            string descriptionStr = regex_replace(description->GetText(), r, string(""));
            string contentStr = regex_replace(content->GetText(), r, string(""));
            rss.description = regex_replace(descriptionStr, r2, string(""));
            rss.content = regex_replace(contentStr, r2, string(""));
            _rss.push_back(rss);
            item = item->NextSiblingElement("item");
        }
    }
    //输出
    void dump(const string & filename){
        ofstream ofs(filename);
        if(!ofs.good()){
            cout << "ofstream open " << filename << " error!" << endl;
            return;
        }
        for(size_t i = 0; i < _rss.size(); ++i){
            ofs << "<doc>" << endl;
            ofs << "<docid>" << i << "</docid>" << endl;
            ofs << "<title>" << _rss[i].title << "</title>" << endl;
            ofs << "<link>" << _rss[i].link << "</link>" << endl;
            ofs << "<description>" << _rss[i].description << "</description>" << endl;
            ofs << "<content>" << _rss[i].content << "</content>" << endl;
            ofs << "</doc>" << endl;
        }
        ofs.close();
    }
private:
    vector<RssItem> _rss;
};  

int main() {
    RssReader reader;
    reader.parseRss();
    reader.dump("pagelib.txt");
    return 0;
}