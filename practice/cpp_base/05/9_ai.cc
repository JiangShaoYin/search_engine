#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;

/*统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频。

输入：某篇文章的绝对路径

输出：词典文件dict.txt（词典中的内容为每一行都是一个“单词 词频”）

词典的存储格式如下。

|   a 66          |
|   abandon 77    |
|   public 88     |
|    ...........  |
|_________________|
代码设计：

struct Record
{
	string _word;
	int _frequency;
};

class Dictionary
{
public:
	//......
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};*/

struct Record {
    string _word;
    int _frequency;
};

class Dictionary {
public:
    void read(const string &filename) {
        ifstream ifs(filename);
        if(!ifs.good()) {
            cout << "ifstream error" << endl;
            return;
        }

        string word;
        while(ifs >> word){
            if(!wordCheck(word)) {
                continue;
            }
            unsigned long i = 0;
            for(i = 0; i < _dict.size(); ++i) {
                if(_dict[i]._word == word){
                    _dict[i]._frequency ++;
                    break;
                }
            }
            if(i == _dict.size()) {
               Record r;
               r._word = word;
               r._frequency = 1;
               _dict.push_back(r);
            }
        }
    }
    void store(const string &filename) {
        ofstream ofs(filename);
        if(!ofs.good()){
            cout << "ofstream error" << endl;
            return;
        }
        for(auto & meb : _dict) {
            ofs << meb._word << " " << meb._frequency << endl;
        }
    }
private:
    bool wordCheck(string & word) {
        for(auto & meb : word) {
            if ((meb < 'a' || meb >'z') && (meb < 'A' || meb > 'Z')){
                return false;
            }
        }
        return true;
    }
    vector<Record> _dict;
};

int main() {
    Dictionary dict;
    dict.read("/home/zhao/Downloads/The_Holy_Bible.txt");
    dict.store("/home/zhao/Downloads/dict.txt");
    return 0;
}
