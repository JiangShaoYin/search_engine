#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
using namespace std;

struct QueryResult {
    string _word;
    int _frequency;
    set<int> _lines;
};

class TextQuery {
public:
    void readFile(const string filename){
        ifstream ifs(filename);
        if(!ifs.good()){
            cout << "file open error" << endl;
            return;
        }
        string line;
        int lineNum = 0;
        while(getline(ifs, line)){
            _lines.push_back(line);
            ++lineNum;
            string word;
            for(auto & ele : line){
                if(!isalpha(ele)){
                    ele = ' ';
                }
            }
            istringstream iss(line);
            while( iss >> word ){
                _dict[word]++;
                _wordNumbers[word].insert(lineNum);
            }
        }     
    }
    QueryResult query(const string &word){
        QueryResult res;
        res._word = word;
        res._frequency = _dict[word];
        res._lines = _wordNumbers[word];
        return res;
        // return { word, _dict[word], _wordNumbers[word]};
    }
    void print(const QueryResult & res) const {
        cout << "-------------------------------------------" << endl;        
        cout << res._word << " occurs " << res._frequency << "times." << endl;
        for(auto ele : res._lines) {
            cout << "(line " << ele << ") " << _lines[ele - 1] << endl;
        }
        cout << "-------------------------------------------" << endl;        
    }
private:
    vector<string> _lines;                // O(1)
    map<string, set<int> > _wordNumbers;  // the the
    map<string, int> _dict;               //
};

// 程序测试用例
int main(int argc, char *argv[]) {
    string queryWord("will");
    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.print(tq.query(queryWord));
    return 0;
}
