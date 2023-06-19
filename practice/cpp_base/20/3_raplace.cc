#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Replace {
    public:
        Replace(const string & dic_path, const string & input_path) {
            loadDic(dic_path);
            replaceFile(input_path);
        }
        void loadDic(const string & dic_path) {
            ifstream ifs(dic_path);
            if(!ifs) {
                cout << "ifstream open " << dic_path << " error" << endl;
                return;
            }
            string line;
            while(getline(ifs, line)) {
                size_t pos = line.find(" ");
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                _dic_map.insert(make_pair(key, value));
            }

        }
        void loadInput(const string & input_path) {
            ifstream ifs(input_path);
            if(!ifs) {
                cout << "ifstream open " << input_path << " error" << endl;
                return;
            }
            string line;
            int line_num = 0;
            while(getline(ifs, line)) {
                string word;
                line_num++;
                _line_map.insert(make_pair(line_num, vector<string>()));
                for(auto & elem : line) {
                    if(isblank(elem)) {
                        _line_map[line_num].push_back(word);
                        word.clear();
                    } else {
                        word += elem;
                    }
                }
                _line_map[line_num].push_back(word);
                word.clear();
            }
            ifs.close();
        }
        void replace() {
            for(auto & line : _line_map) {
                for(auto & word : line.second) {
                    auto it = _dic_map.find(word);
                    if(it != _dic_map.end()) {
                        word = it->second;
                    }
                }
            }
        }
        void replaceFile(const string & input_path) {
            loadInput(input_path);
            replace();
            ofstream ofs(input_path);
            if(!ofs) {
                cout << "ofstream open " << input_path << " error" << endl;
                return;
            }
            for(auto & line : _line_map) {
                for(auto & word : line.second) {
                    ofs << word << " ";
                }
                ofs << endl;
            }
            ofs.close();
        }


        void print() const {
            for(auto & line : _line_map) {
                for(auto & word : line.second) {
                    cout << word << " ";
                }
                cout << endl;
            }
        }
    private:
    map<string, string> _dic_map;
    map<int, vector<string>> _line_map;
};

int main() {
    Replace r("map.txt", "file.txt");
    return 0;
}