#include "searchFile.hh"

// TextQuery类实现，用于读取文件，保存文件内容，以及查询
// 测试代码
/*
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <memory>
using namespace std;

struct QueryResult {
  string _word;
  int _frequency;
  set<int> _lines;
  shared_ptr<vector<string>> _file;    // 储存文件内容
};

class TextQuery {
public:
    void readFile(const string filename);
    QueryResult query(const string &word);
    // void print(const QueryResult & res) const;
private:
    vector<string> _lines;                // 储存每一行的信息
    map<string, set<int> > _wordNumbers;  // 储存每个单词，以及其存在的行
    map<string, int> _dict;               // 储存每个单词，以及其出现的次数
};
*/

// 读取文件，保存文件内容
void TextQuery::readFile(const string filename) {
  ifstream ifs(filename); //打开文件
  if (!ifs.good()) {
    cout << "file open error" << endl;
    return;
  }
  string line; 
  int lineNum = 0;
  while (getline(ifs, line)) { // 读取每一行
    _lines.push_back(line);
    ++lineNum;
    string word;
    for (auto &ele : line) {
      if (!isalpha(ele)) {
        ele = ' ';
      }
    }
    istringstream iss(line); 
    while (iss >> word) { // 读取每个单词
      _dict[word]++;
      _wordNumbers[word].insert(lineNum);
    }
  }
}

// 查询函数，返回查询结果
QueryResult TextQuery::query(const string &word) const {
  QueryResult res;
  res._word = word; // 放入单词
  // 放入文件内容
  // res._file = make_shared<vector<string>>(_lines); //要用make_shared，否则会出现段错误，原因是shared_ptr的构造函数是explicit的
  res._file = shared_ptr<vector<string>>(new vector<string>(_lines));
  // 如果单词不存在，返回空的QueryResult
  if(_dict.find(word) == _dict.end()) {
    res._frequency = 0;
    res._lines = set<int>();
    return res;
  }
  // 单词存在
  res._frequency = _dict.find(word)->second; // 放入单词出现次数
  res._lines = _wordNumbers.find(word)->second; // 放入单词出现的行号
  return res;
}

// 程序测试用例
/* 
int main(int argc, char *argv[]) {
    string queryWord("she");
    TextQuery tq;
    tq.readFile("Sample.txt");
    QueryResult res = tq.query(queryWord);
    cout << res;
    return 0;
}
*/
