#include "searchFile.hh"

// QueryResult输出运算符重载，输出查询结果
ostream &operator<<(ostream &os, const QueryResult &res) {
    os << "-------------------------------------------" << endl;
    os << res._word << " occurs " << res._frequency << " times." << endl;
    for (auto ele : res._lines) {
        os << "(line " << ele << ") " << res._file->at(ele - 1) << endl;
    }
    os << "-------------------------------------------" << endl;
  return os;
}
ostream &operator<<(ostream &os, const Query &res){
    os << res.rep();
    return os;
}

int main(){
    string filename = "Sample.txt";
    TextQuery tq;
    // 此时，file的所有内容都被放在了内存中（tq中）
    tq.readFile(filename);
    // QueryResult res = tq.query("sjhghe");
    Query q1 = Query("she") | Query("him") & ~Query("he") & ~Query("her");
    cout << q1 << endl;
    QueryResult res = q1.eval(tq);
    cout << res;
    return 0;
}