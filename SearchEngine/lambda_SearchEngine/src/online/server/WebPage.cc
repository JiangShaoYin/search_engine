#include "../../../include/WebPage.h"

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "../../../include/Configuration.h"
#include "../../../include/CppJieba.h"
#include "../../../include/log4pp.h"

using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

WebPage::WebPage(int docId, const string& docTitle, const string& docUrl, const string& docContent)
    : _docId(docId), _docTitle(docTitle), _docUrl(docUrl), _docContent(docContent) {}
WebPage::~WebPage() {}

int WebPage::getDocId() const { return _docId; }                // 获取文档id
string WebPage::getTitle() const { return _docTitle; }          // 获取文档标题
string WebPage::setSummary(const vector<string>& queryWords) {  // 生成文档摘要g
                                                                // 1.获取文档内容的分词结果
  auto _wordCutTool = SplitToolCppJieba::GetInstance(Configuration::GetInstance("").get());
  vector<string> wordsVec = _wordCutTool->cut(_docContent);
  // 2.将查询词放入set
  set<string> queryWordsSet;
  for (auto& word : queryWords) {
    queryWordsSet.insert(word);
  }
  // 3.遍历分词结果，将查询词前后20词放入vector
  vector<string> summaryVec;
  for (int i = 0; i < wordsVec.size(); ++i) {
    string word = wordsVec[i];
    // 若当前单词在查询词中，则将其前后20个单词放入vector，并且删除查询词中的该单词
    if (queryWordsSet.find(word) != queryWordsSet.end()) {
      // 确定it向前向后20的位置
      int begin = i;
      int end = i;
      end++;
      int count = 0;
      int beginFlag = 1;
      int endFlag = 1;
      while (count < 20) {
        count++;
        if (beginFlag) {
          (begin == 0) ? begin : --begin;
          if (begin == 0) {
            beginFlag = 0;
          }
          // 如果wordsVec[begin]是句号或者空格，则停止向前搜索
          if (wordsVec[begin] == "。") {
            begin++;
            beginFlag = 0;
          }
        }
        (end == wordsVec.size()) ? end : ++end;
      }
      // 此时，begin和end分别指向了向前向后20的位置，区间为[begin, end)，将区间内的单词放入vector
      while (begin != end) {
        if (begin == i) {
          // 将当前单词变为红色
          summaryVec.push_back("\033[31m");
          summaryVec.push_back(wordsVec[begin]);
          summaryVec.push_back("\033[0m");

        } else {
          summaryVec.push_back(wordsVec[begin]);
        }
        begin++;
      }
      // 最后放入省略号与换行符
      summaryVec.push_back("...");
      // 删除查询词中的该单词
      auto it = queryWordsSet.find(word);
      queryWordsSet.erase(it);
    }
  }
  // 4.将vector中的单词拼接成字符串
  for (auto& word : summaryVec) {
    _docSummary += word;
  }
  return _docSummary;
}
string WebPage::getSummary() const { return _docSummary; }  // 获取文档摘要
string WebPage::getUrl() const { return _docUrl; }          // 获取文档url
string WebPage::getContent() const { return _docContent; }  // 获取文档内容
