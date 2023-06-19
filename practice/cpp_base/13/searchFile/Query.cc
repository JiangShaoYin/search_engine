#include "searchFile.hh"

// -------------------------------WordQuery begin----------------------------------------
class WordQuery : public Query_base {
    friend class Query;

    WordQuery(const string &s) : _word(s) {}
    QueryResult eval(const TextQuery &)const;
    string rep() const{ return _word; }
    string _word;
};
// 实现WordQuery的eval函数
QueryResult WordQuery::eval(const TextQuery & t) const { return t.query(_word);}

// 实现Query类string参数的构造函数
Query::Query(const string &s) : _p(new WordQuery(s)) {}

// ----------------------------------NotQuery begin----------------------------------------
class NotQuery : public Query_base {
    // 设置友元才能访问私有构造函数
    friend Query operator~(const Query & q);
    NotQuery(const Query & q):_q(q) {}
    QueryResult eval(const TextQuery &) const;
    string rep() const { return "~(" + _q.rep() + ")"; }
    Query _q; // 保存的是满足条件的Query对象，需要取反
};
// 实现NotQuery的eval函数
QueryResult NotQuery::eval(const TextQuery & t) const{
    // 得到满足条件的QueryResult对象
    QueryResult exclude = _q.eval(t); 
    // 保存最终的结果
    QueryResult res;
    res._word = "~(" + exclude._word + ")"; // 保存单词
    res._file = exclude._file; // 保存文件内容
    // 遍历所有行，将不在exclude中的行添加到res中
    for(int i = 0; i < res._file->size(); ++i){
        // 如果当前行不在exclude中，就将其添加到res中
        int line = i + 1;
        if(exclude._lines.find(line) == exclude._lines.end()){
            res._lines.insert(line);
        }
    }
    // 保存单词未出现的次数（行数）
    res._frequency = res._lines.size();
    return res;
}
// 通过传进来的Query对象，生成NotQuery对象
// 然后通过NotQuery的智能指针生成新的Query对象并返回
Query operator~(const Query & q){
    Query res(shared_ptr<Query_base>(new NotQuery(q)));
    return res;
}
// ---------------------------BinaryQuery begin----------------------------------
class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query & lhs, const Query & rhs, string opSym) : _lhs(lhs), _rhs(rhs), _opSym(opSym) {}
    string rep() const { return "(" + _lhs.rep() + " " + _opSym + " " + _rhs.rep() + ")"; }
    Query _lhs, _rhs; // 左右操作数
    string _opSym; // 操作符的符号
};
// --------------------------------AndQuery begin--------------------------------
class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query & lhs, const Query & rhs) : BinaryQuery(lhs, rhs, "&") {}
    QueryResult eval(const TextQuery & t) const;
};
// 实现AndQuery的eval函数
QueryResult AndQuery::eval(const TextQuery & t) const{
    // 得到左右操作数的QueryResult对象，取交集
    QueryResult left = _lhs.eval(t), right = _rhs.eval(t);
    // 保存最终的结果
    QueryResult res;
    res._word = "(" + left._word + " & " + right._word + ")"; // 保存单词
    res._file = left._file; // 保存文件内容
    for(int i = 0; i < res._file->size(); ++i){
        int line = i + 1;
        if(left._lines.find(line) != left._lines.end() 
        && right._lines.find(line) != right._lines.end()){
            res._lines.insert(line);
        }
    }
    res._frequency = res._lines.size();
    return res;
}
// 重载&操作符
Query operator&(const Query & lhs, const Query & rhs){
    Query res(shared_ptr<Query_base>(new AndQuery(lhs, rhs)));
    return res;
}

// --------------------------------OrQuery begin---------------------------------
class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query & lhs, const Query & rhs) : BinaryQuery(lhs, rhs, "|") {}
    QueryResult eval(const TextQuery &) const;
};                                                           
// 实现OrQuery的eval函数
QueryResult OrQuery::eval(const TextQuery & t) const{
    QueryResult left = _lhs.eval(t), right = _rhs.eval(t);
    // 保存最终的结果
    QueryResult res;
    res._word = "(" + left._word + " | " + right._word + ")"; // 保存单词
    res._file = left._file; // 保存文件内容
    for(int i = 0; i < res._file->size(); ++i){
        int line = i + 1;
        //  取并集
        if(left._lines.find(line) != left._lines.end() 
        || right._lines.find(line) != right._lines.end()){
            res._lines.insert(line);
        }
    }
    res._frequency = res._lines.size();
    return res;
}
// 重载|操作符
Query operator|(const Query & lhs, const Query & rhs){
    Query res(shared_ptr<Query_base>(new OrQuery(lhs, rhs)));
    return res;
}