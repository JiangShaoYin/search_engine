#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <memory>
using namespace std;

// 查询结果结构体
struct QueryResult {
  string _word; // 单词
  int _frequency;
  set<int> _lines;
  shared_ptr<vector<string>> _file;    // 储存文件内容
};

// TextQuery类，用于读取文件，保存文件内容，以及查询
class TextQuery {
public:
    void readFile(const string filename);
    QueryResult query(const string &word) const;
    // void print(const QueryResult & res) const;
private:
    vector<string> _lines;                // 储存每一行的信息
    map<string, set<int> > _wordNumbers;  // 储存每个单词，以及其存在的行
    map<string, int> _dict;               // 储存每个单词，以及其出现的次数
};

// 搜索抽象类
class Query_base {
  friend class Query;
 protected:
  using line_no = vector<string>::size_type;
  virtual ~Query_base() = default;

 private:
  virtual QueryResult eval(const TextQuery &) const = 0;
  virtual string rep() const = 0;
};

// 最外层的搜索类
class Query {
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

 public:
  // 公有化使用string的构造函数，根据string生成WordQuery
  // 该构造函数只有声明，要到后面定义WordQuery类时实现
  Query(const string &s);
  // 查询
  QueryResult eval(const TextQuery & t) const { return _p->eval(t); }
  //输出
  string rep() const { return _p->rep(); }

 private:
  // 私有化构造函数
  Query(shared_ptr<Query_base> query) : _p(query) {}
  // 保存Query_base的指针
  shared_ptr<Query_base> _p;
};
