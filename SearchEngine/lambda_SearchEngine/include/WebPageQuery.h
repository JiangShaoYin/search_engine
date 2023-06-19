#pragma once
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>


using std::pair;
using std::set;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

class WebPage;

class WebPageQuery {
 public:
  WebPageQuery();
  ~WebPageQuery();
  // 执行查询
  string DoQuery(const string& key);

 private:
  // 加载语料库
  void LoadLibrary(const string& path);
  // 获取查询词的权重向量
  vector<double> GetQueryWordsWeightVector(const vector<string>& queryWords);
  // 执行查询，查出的结果存入resultVec中，其中int为文章id，vector<double>为文章的权重向量，queryWords为查询词
  bool ExecuteQuery(const vector<string>& queryWords, vector<pair<int, vector<double>>>& resultVec);
  // 根据向量夹角计算相似度
  double ComputeSimilarity(vector<double>& lhs, vector<double>& rhs);
  // 根据文章id列表，和查询词列表，获取对应WebPage
  void GetWebPage(const vector<pair <int, double>>& docIdVec, const vector<string>& queryWords, string & dataDirPath);
  // 创建json字符串，resultVec为查询结果，其中int为文章id，vector<double>为文章的权重向量，queryWords为查询词
  string CreateJson(vector<pair<int, double>>& resultVecWithSimilarity, const vector<string>& queryWords);

 private:
  static vector<pair<int, WebPage>> page_lib_;                       // 存储网页库,文章id,网页
  static unordered_map<int, pair<int, int>> offset_lib_;              // 偏移库，文章id(起始位置，长度)
  static unordered_map<string, set<pair<int, double>>> invert_index_;  // 倒排索引表，词，文章id，权重
};
