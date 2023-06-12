#ifndef __KEYRECOMMANDER_H__
#define __KEYRECOMMANDER_H__

#include "Server_TcpConnection.h"
#include "CnDictionary.h"
#include "EngDictionary.h"
#include "EditDistance.h"
#include <queue>
#include <set>
#include <string>
#include <memory>
#include <iostream>

struct MyResult
{
    string word;
    int frequency;
    int distance;
};

struct MyCompare
{
    bool operator()(const MyResult & lhs,const MyResult & rhs) const
    {
        if (lhs.distance != rhs.distance) 
        {
            return lhs.distance > rhs.distance;
        }
        else if (lhs.frequency != rhs.frequency) 
        {
            return lhs.frequency < rhs.frequency;
        }
        else if (lhs.word != rhs.word) {
            return lhs.word < rhs.word;
        }
        return false;
    }
};

using std::priority_queue;
using std::set;
using std::string;
using std::cout;
using std::endl;

class KeyRecommander
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
public:
    KeyRecommander(string , const TcpConnectionPtr &,
                   CnDictionary & ,EngDictionary &);
    ~KeyRecommander();
    void doQuery();
    string getResult();
    //pd is_chinese
    bool isChinese(const string & str);
private:
    string _queryWord;//未初始化的候选词
    string _jsonstring;//json化的最终结果
    vector<string> querywords;//切割好的候选词
    vector<string> finalresult;//最终的查询结果
    TcpConnectionPtr _con;
    CnDictionary & _cndict;
    EngDictionary & _engdict;
    set<int> _queryresult;//临时用的合并set
    priority_queue<MyResult,vector<MyResult>,MyCompare> CandidateResult;//候选排序结果
    EditDistance _editdist;
};

#endif
