#pragma once
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class WebPage {
 public:
  WebPage(int docId, const string& docTitle, const string& docUrl, const string& docContent);
  ~WebPage();

  int GetDocId() const;                            // 获取文档id
  string GetTitle() const;                             // 获取文档标题
  string SetSummary(const vector<string>& queryWords); // 生成文档摘要
  string GetSummary() const;                    // 获取文档摘要
  string GetUrl() const;                                      // 获取文档url
  string GetContent() const;                              // 获取文档内容

 private:
  int docId_;          // 文档id
  string docTitle_;    // 文档标题
  string docUrl_;      // 文档url
  string docContent_;  // 文档内容
  string docSummary_;  // 文档摘要
};