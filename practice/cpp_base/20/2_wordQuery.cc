#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

class Query{
public:
    Query(const string & srcPath, const string & dictPath) {
        loadDict(srcPath);
        writeCount(dictPath);
    }
private:
    void loadDict(const string & srcPath) {
        ifstream ifs(srcPath);
        if(!ifs) {
            cout << "ifstream open " << srcPath << " error" << endl;
            return;
        }
        string line;
        while(getline(ifs,line)) {
            for(auto & elem : line) {
                if(!isalpha(elem)) {
                    elem = ' ';
                }
            }
            istringstream iss(line);
            string word;
            while(iss >> word) {
                _dict[word]++;
            }
        }
        ifs.close();
    }

    void writeCount(const string & dictPath) {
        ofstream ofs(dictPath);
        if(!ofs) {
            cout << "ofstream open " << dictPath << " error" << endl;
            return;
        }
        for(auto & elem : _dict) {
            ofs << elem.first << " " << elem.second << endl;
        }
    }
    unordered_map<string, int> _dict;
};

int main() {
    Query q("china_daily.txt", "dict.txt");
    return 0;
}