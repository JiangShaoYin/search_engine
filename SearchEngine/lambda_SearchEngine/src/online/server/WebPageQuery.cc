#include "../../../include/WebPageQuery.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../include/Configuration.h"
#include "../../../include/CppJieba.h"
#include "../../../include/WebPage.h"
#include "../../../include/log4pp.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;
using json = nlohmann::json;

vector<pair<int, WebPage>> WebPageQuery::page_lib_ = vector<pair<int, WebPage>>();
unordered_map<int, pair<int, int>> WebPageQuery::offset_lib_ = unordered_map<int, pair<int, int>>();
unordered_map<string, set<pair<int, double>>> WebPageQuery::invert_index_ = unordered_map<string, set<pair<int, double>>>();

WebPageQuery::WebPageQuery() {
}

WebPageQuery::~WebPageQuery() {
}

// 执行查询
string WebPageQuery::DoQuery(const string& key) {
  // 1. 读取配置文件
  auto conf = Configuration::GetInstance("");
  logInfo("网页查询 - WebPageQuery::doQuery, 读取配置文件完成！");
  // 2. 获取语料库路径
  string pageLibPath = conf->getConfigMap("onlinedata");
  logInfo("网页查询 - WebPageQuery::doQuery, 从config获取的pageLibPath: " + pageLibPath);
  // 2. 加载偏移库与倒排索引库
  LoadLibrary(pageLibPath);
  logInfo("网页查询 - WebPageQuery::doQuery, 加载偏移库与倒排索引库完成！");
  logInfo("网页查询 - WebPageQuery::doQuery, 偏移库大小：" + std::to_string(offset_lib_.size()));
  logInfo("网页查询 - WebPageQuery::doQuery, 倒排索引库大小：" + std::to_string(invert_index_.size()));
  // 3. 获取查询词
  auto _wordCutTool = SplitToolCppJieba::GetInstance(Configuration::GetInstance("").get());
  vector<string> queryWords = _wordCutTool->cut(key);
  // 删除分词结果中的空格和换行符
  for (auto it = queryWords.begin(); it != queryWords.end();) {
    if (*it == "" || *it == "\n" || *it == " ") {
      it = queryWords.erase(it);
    } else {
      ++it;
    }
  }
  logInfo("网页查询 - WebPageQuery::doQuery, 获取查询词完成, 查询词个数：" + std::to_string(queryWords.size()));
  string logQueryWords = "网页查询 - WebPageQuery::doQuery, 查询词 : ";
  int i = 0;
  for (auto& item : queryWords) {
    logQueryWords += item + " ";
  }
  logInfo(logQueryWords);
  // 3. 获取查询词的权重向量， baseVector
  vector<double> queryWordsWeightVector = GetQueryWordsWeightVector(queryWords);
  logInfo("网页查询 - WebPageQuery::doQuery, 获取查询词的权重向量完成");
  // 4. 执行查询，查出的结果存入resultVec中，其中int为文章id，vector<double>为文章的权重向量，queryWords为查询词
  vector<pair<int, vector<double>>> resultVec;
  bool res = ExecuteQuery(queryWords, resultVec);
  if (!res) {
    logInfo("网页查询 - WebPageQuery::doQuery, 未查到相关文章！");
    return string("未查到相关文章！");
  }
  logInfo("网页查询 - WebPageQuery::doQuery, 执行查询完成，查到相关文章个数：" + std::to_string(resultVec.size()));
  // 5. 根据向量夹角计算相似度 resresultVecWithSimilarity : <文章id, 相似度>
  vector<pair<int, double>> resultVecWithSimilarity;
  for (auto& item : resultVec) {
    double similarity = ComputeSimilarity(item.second, queryWordsWeightVector);
    resultVecWithSimilarity.push_back(std::make_pair(item.first, similarity));
  }
  // 6. 根据相似度从大到小排序，结果存入容器中
  std::sort(resultVecWithSimilarity.begin(), resultVecWithSimilarity.end(), [](const pair<int, double>& lhs, const pair<int, double>& rhs) {
    return lhs.second > rhs.second;
  });
  logInfo("网页查询 - WebPageQuery::doQuery, 根据相似度从大到小排序完成");
  // 7. 根据查询结果，在网页库中搜索对应的网页，获取网页的url、title、content
  GetWebPage(resultVecWithSimilarity, queryWords, pageLibPath);
  logInfo("网页查询 - WebPageQuery::doQuery, 搜索目标网页完成");
  // 7. 创建json字符串，resultVec为查询结果，其中int为文章id，vector<double>为文章的权重向量，queryWords为查询词
  string json = CreateJson(resultVecWithSimilarity, queryWords);
  logInfo("网页查询 - WebPageQuery::doQuery, 创建json字符串完成, 返回json字符串");
  // 8. 返回json字符串
  return json;
}

// 加载偏移库与倒排索引库
void WebPageQuery::LoadLibrary(const string& path) {
  string line;
  if (offset_lib_.size() == 0) {
    // 偏移库文件 offsettest.dat
    string offsetPath = path + "/offsettest.dat";
    logInfo("网页查询 - 磁盘加载偏移库文件");
    ifstream offsetIfs(offsetPath);
    if (!offsetIfs.good()) {
      logError("网页查询 - 磁盘加载偏移库文件失败");
      return;
    }
    while (getline(offsetIfs, line)) {
      int id;
      int offset;
      int len;
      istringstream iss(line);
      iss >> id >> offset >> len;
      offset_lib_.insert(std::make_pair(id, std::make_pair(offset, len)));
    }
    offsetIfs.close();
  }

  if (invert_index_.size() == 0) {
    // 倒排索引表文件 Inverttest.dat
    string invertIndexTablePath = path + "/Inverttest.dat";
    logInfo("网页查询 - 磁盘加载倒排索引表文件");
    ifstream invertIndexTableIfs(invertIndexTablePath);
    if (!invertIndexTableIfs.good()) {
      logError("网页查询 - 磁盘加载倒排索引表文件失败");
      return;
    }
    while (getline(invertIndexTableIfs, line)) {
      string word;    // 单词
      int docId;      // 文档id
      double weight;  // 单词在文档中的权重
      istringstream iss(line);
      iss >> word;                      // 首先取出单词
      while (iss >> docId >> weight) {  // 循环取出 docId 和 weight
        invert_index_[word].insert(std::make_pair(docId, weight));
      }
    }
    invertIndexTableIfs.close();
  }
}

// 获取查询词的权重向量
vector<double> WebPageQuery::GetQueryWordsWeightVector(const vector<string>& queryWords) {
  map<string, int> queryWordsMap;
  for (auto& word : queryWords) {
    ++queryWordsMap[word];
  }
  // 使用TF-IDF 算法 计算查询词的权重向量
  vector<double> queryWordsWeightVector;
  double weightSum = 0;
  for (auto& word : queryWords) {
    // 1. 取出查询词在查询语句中的词频
    int tf = queryWordsMap[word];
    // 2. 取出包含该词语的文档数
    int df = invert_index_[word].size();
    // 3. 计算该文档的逆文档频率
    int docNum = offset_lib_.size();
    double idf = log(docNum / (df + 1)) / log(2);
    // 4. 计算该词语的权重
    double weight = tf * idf;
    queryWordsWeightVector.push_back(weight);
  }
  return queryWordsWeightVector;
}

// 执行查询，查出的结果存入resultVec中，其中int为文章id，vector<double>为文章的权重向量，queryWords为查询词
bool WebPageQuery::ExecuteQuery(const vector<string>& queryWords, vector<pair<int, vector<double>>>& resultVec) {
  // 1. 获取目标文档集合
  set<int> docIdSet;
  for (auto& word : queryWords) {
    set<int> tmpSet;
    // 首先找出包含该词语的文档集合
    set<pair<int, double>> indexList = invert_index_[word];
    for (auto& pair : indexList) {
      // 将文档id存入临时集合中
      tmpSet.insert(pair.first);
    }
    // 将临时集合与总集合求交集
    if (docIdSet.empty()) {
      docIdSet = tmpSet;
    } else {
      set<int> tmp;
      set_intersection(docIdSet.begin(), docIdSet.end(), tmpSet.begin(), tmpSet.end(), inserter(tmp, tmp.begin()));
      docIdSet = tmp;
    }
  }
  // 2. 计算每个文档的权重向量
  for (auto& docId : docIdSet) {
    // 2.1 配合倒排索引，获取该文档每个查询词的权重
    vector<double> docWeightVector;
    for (auto& word : queryWords) {
      // 2.2 获取该词语在该文档中的权重
      set<pair<int, double>> indexList = invert_index_[word];
      double weight = 0;
      for (auto& pair : indexList) {
        if (pair.first == docId) {
          weight = pair.second;
          break;
        }
      }
      docWeightVector.push_back(weight);
    }
    // 文章id -> 文章的权重向量vector<double>
    resultVec.push_back(std::make_pair(docId, docWeightVector));
  }
  // 判断结果集合是否为空
  if (resultVec.empty()) {
    return false;
  }
  return true;
}

// 根据向量夹角计算相似度
double WebPageQuery::ComputeSimilarity(vector<double>& lhs, vector<double>& rhs) {
  // 利用两个向量夹角的余弦值计算相似度
  // 1. 计算两个向量的模
  double lhsNorm = 0;
  double rhsNorm = 0;
  for (int i = 0; i < lhs.size(); ++i) {
    lhsNorm += lhs[i] * lhs[i];
    rhsNorm += rhs[i] * rhs[i];
  }
  lhsNorm = sqrt(lhsNorm);
  rhsNorm = sqrt(rhsNorm);
  // 2. 计算两个向量的内积
  double innerProduct = 0;
  for (int i = 0; i < lhs.size(); ++i) {
    innerProduct += lhs[i] * rhs[i];
  }
  // 3. 计算两个向量的夹角余弦值
  double cosValue = innerProduct / (lhsNorm * rhsNorm);
  // 余弦值越大，两个向量越相似
  return cosValue;
}

void WebPageQuery::GetWebPage(const vector<pair<int, double>>& docIdVec, const vector<string>& queryWords, string& dataDirPath) {
  string pageLibPath = dataDirPath + "/pagetest.dat";
  ifstream ifs(pageLibPath);
  // 1. 遍历docIdVec，分别找出对应文章的偏移量和长度
  for (auto& pair : docIdVec) {
    // 获取文章id
    int docId = pair.first;
    // 查看当前文章是否已经被处理过
    bool flag = false;
    for (auto& item : page_lib_) {
      int idNum = item.first;
      if (docId == idNum) {
        flag = true;
        break;
      }
    }
    if (flag) {
      continue;
    }
    // 根据文章id获取文章偏移量和长度
    int off = offset_lib_[docId].first;
    int len = offset_lib_[docId].second;
    // 2. 根据偏移量和长度获取文章内容
    ifs.seekg(off, ifs.beg);
    char* buf = new char[len + 1]();
    ifs.read(buf, len);
    string doc(buf);
    // 3. 将文章内容存入_pageLib中
    // 3.1 获取文章id
    int idBeg = doc.find("<docid>");
    int idEnd = doc.find("</docid>");
    string docIdStr = doc.substr(idBeg + 7, idEnd - idBeg - 7);
    // 3.2 获取文章标题
    int docTitleBeg = doc.find("<title>");
    int docTitleEnd = doc.find("</title>");
    string docTitle = doc.substr(docTitleBeg + 7, docTitleEnd - docTitleBeg - 7);
    // 3.3 获取文章链接
    int docUrlBeg = doc.find("<url>");
    int docUrlEnd = doc.find("</url>");
    string docUrl = doc.substr(docUrlBeg + 5, docUrlEnd - docUrlBeg - 5);
    // 3.4 获取文章内容
    int docContentBeg = doc.find("<description>");
    int docContentEnd = doc.find("</description>");
    string docContent = doc.substr(docContentBeg + 13, docContentEnd - docContentBeg - 13);
    // 装载文章
    WebPage webPage(docId, docTitle, docUrl, docContent);
    // 3.5生成文章摘要
    string summary = webPage.SetSummary(queryWords);
    // 3.6 将文章存入_pageLib中
    page_lib_.push_back(std::make_pair(docId, webPage));
    // 4. 释放内存
    delete[] buf;
  }
  ifs.close();
}

void to_json(json& j, const WebPage& p) {
  j = json{{"id", p.GetDocId()},
           {"title", p.GetTitle()},
           {"url", p.GetUrl()},
           {"summary", p.GetSummary()}};
}

// 创建json字符串，resultVecWithSimilarity为查询结果，其中int为文章id，double为文章的相似度，queryWords为查询词
string WebPageQuery::CreateJson(vector<pair<int, double>>& resultVecWithSimilarity, const vector<string>& queryWords) {
  // 1. 根据resultVecWithSimilarity中的文章id，找到_pageLib中对应的文章
  vector<WebPage> webPageVec;
  for (auto& pair : resultVecWithSimilarity) {
    int docId = pair.first;
    for (auto& pagePair : page_lib_) {
      if (pagePair.first == docId) {
        webPageVec.push_back(pagePair.second);
        break;
      }
    }
  }

  // 2. 将文章信息转换成json字符串
  json j = webPageVec;
  // 3. 将json字符串转换成string
  string jsonStr = j.dump();
  return jsonStr;
}
