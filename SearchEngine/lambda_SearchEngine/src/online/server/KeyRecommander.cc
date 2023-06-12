#include "../../../include/KeyRecommander.h"
#include "../../../include/CppJieba.h"
#include "../../../include/Configuration.h"
#include "../../../include/log4pp.h"
#include <nlohmann/json.hpp>
#include <locale>
#include <codecvt>
#include <sstream>
#include <algorithm>

using json = nlohmann::json;
using std::istringstream;
using std::wstring;
using std::locale;
using std::wstring_convert;
using std::codecvt_utf8;
using std::set_union;

KeyRecommander::KeyRecommander(string query,const TcpConnectionPtr & con
                               ,CnDictionary & cndict,EngDictionary & engdict)
:_queryWord(query)
,_con(con)
,_cndict(cndict)
,_engdict(engdict)
{
    //初始化切割关键词
    string str(_queryWord); 
    wstring wstr;
    wstring result;
    locale loc("");
    // 将 UTF-8 编码的 std::string 转换为 std::wstring
    wstring_convert<codecvt_utf8<wchar_t>> converter;
        wstr = converter.from_bytes(str);
    for (auto it = wstr.begin(); it != wstr.end(); ++it) {
        if (*it > 0 && *it < 128) {
            // 英文字符
            result += *it;
            if (it + 1 != wstr.end() && *(it + 1) > 127) {
                result += L" ";
            }
        } else {
            // 中文字符
            result += *it;
            if (it + 1 != wstr.end() && *(it + 1) > 0 && *(it + 1) < 128) {
                result += L" ";
            }
        }
    }
    string utf8 = converter.to_bytes(result);
    //utf8为切割好的queryword，并将其放入querywords
    istringstream iss(utf8);
    string word;
    while (iss >> word)
    {
        querywords.push_back(word);
    }
    //放好querywords
}

void KeyRecommander::doQuery()
{
    vector<string> needtocut;
    auto _jieba = SplitToolCppJieba::GetInstance(Configuration::GetInstance("").get());
    for (size_t i = 0;i < querywords.size();++i)
    {
        //初始化
        priority_queue<MyResult,vector<MyResult>,MyCompare> empty;
        CandidateResult.swap(empty);
        _queryresult.clear();
        needtocut.clear();
        //切割查询
        string temp(querywords[i]);
        _jieba->cutsmall(temp,needtocut,1);
        logInfo("切候选词");
        if (needtocut.size()){
            if (isChinese(temp))
            {
                //中文
                logInfo("识别出中文");
                for (size_t j = 0;j < needtocut.size();++j)
                {
                    set<int> temp = _cndict.getIndex(needtocut[j]);
                    for (auto & t : temp)
                    {
                        _queryresult.insert(t);
                    }
                }
                //执行完毕 插入CandidateResult
                logInfo("合并set完成");
                for (auto & t : _queryresult)
                {
                     pair<string,int> mypair = _cndict.getDict(t);
                     MyResult myres;
                     myres.word = mypair.first;
                     myres.frequency = mypair.second;
                     myres.distance = _editdist.editDistance(temp,mypair.first);
                     CandidateResult.push(myres);
                }
                logInfo("优先队列完成");
            }
            else 
            {
                //English
                logInfo("识别出英文");
                for (size_t j = 0;j < needtocut.size();++j)
                {
                    set<int> temp = _engdict.getIndex(needtocut[j]);
                    for (auto & t : temp)
                    {
                        _queryresult.insert(t);
                    }
                }
                //执行完毕 插入CandidateResult
                logInfo("合并set完成");
                for (auto & t : _queryresult)
                {
                     pair<string,int> mypair = _engdict.getDict(t);
                     MyResult myres;
                     myres.word = mypair.first;
                     myres.frequency = mypair.second;
                     myres.distance = _editdist.editDistance(temp,mypair.first);
                     CandidateResult.push(myres);
                }
                logInfo("优先队列完成");
            }

        }    
        logInfo("得到finalresult");
        //执行完毕 1 time
        //deal with set
        logInfo("获取候选词");
        for (size_t j = 0;j < 10;++j)
        {
            if (CandidateResult.empty()) break;
            if (CandidateResult.top().word == temp){
               CandidateResult.pop(); 
            }
            finalresult.push_back(CandidateResult.top().word);
            CandidateResult.pop();
        }
        finalresult.push_back("");
        //转换json返回
    }
    json j = finalresult;
    _jsonstring = j.dump();
    logInfo("获取json返回:%s",_jsonstring.c_str());
}

string KeyRecommander::getResult()
{
    return _jsonstring;
}

KeyRecommander::~KeyRecommander()
{

}


bool KeyRecommander::isChinese(const string &str)
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

