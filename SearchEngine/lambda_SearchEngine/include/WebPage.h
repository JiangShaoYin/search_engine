#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

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

  int getDocId() const;                            // 获取文档id
  string getTitle() const;                             // 获取文档标题
  string setSummary(const vector<string>& queryWords); // 生成文档摘要
  string getSummary() const;                    // 获取文档摘要
  string getUrl() const;                                      // 获取文档url
  string getContent() const;                              // 获取文档内容

 private:
  int _docId;          // 文档id
  string _docTitle;    // 文档标题
  string _docUrl;      // 文档url
  string _docContent;  // 文档内容
  string _docSummary;  // 文档摘要
};

#endif
