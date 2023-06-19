#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

class Dictionary {
public:
    void read(const string & filename) {
        ifstream ifs(filename);
        if(!ifs.good()) {
            cout << "ifstream error" << endl;
            return;
        }
        string word;
        while(ifs >> word) {
            if(!wordCheck(word)) {
                continue;
            }
            _dict[word]++;
        }
    }
    void store(const string & filename) {
        ofstream ofs(filename);
        if(!ofs.good()) {
            cout << "ofstream error" << endl;
            return;
        }
        // for(auto & meb : _dict) {
        //     ofs << meb.first << " " << meb.second << endl;
        // }
        for(auto it = _dict.begin(); it != _dict.end(); ++it) {
            ofs << it->first << " " << it->second << endl;
        }
    }
    bool wordCheck(string & word) {
        for (auto & meb : word) {
            if ((meb < 'a' || meb > 'z') && (meb < 'A' || meb > 'Z')) {
                return false;
            }
        }
        return true;
    }
private:
    map<string, int> _dict;
};

int main() {
    Dictionary d;
    d.read("The_Holy_Bible.txt");
    d.store("dict.txt");
    return 0;
}