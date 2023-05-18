#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Record {
  string _word;
  int _frequency;
};

class Dictionary {
 public:
  void read(const string &filename) {
    ifstream ifs(filename);
    if (!ifs.good()) {
      cout << "ifstream error" << endl;
      return;
    }

    string word;
    while (ifs >> word) {
      if (!wordCheck(word)) {
        continue;
      }
      unsigned long i = 0;
      for (i = 0; i < _dict.size(); ++i) {
        if (_dict[i]._word == word) {
          _dict[i]._frequency++;
          break;
        }
      }
      if (i == _dict.size()) {
        Record r;
        r._word = word;
        r._frequency = 1;
        _dict.push_back(r);
      }
    }
  }
  void store(const string &filename) {
    ofstream ofs(filename);
    if (!ofs.good()) {
      cout << "ofstream error" << endl;
      return;
    }
    for (auto &meb : _dict) {
      ofs << meb._word << " " << meb._frequency << endl;
    }
  }

 private:
  bool wordCheck(string &word) {
    for (auto &meb : word) {
      if ((meb < 'a' || meb > 'z') && (meb < 'A' || meb > 'Z')) {
        return false;
      }
    }
    return true;
  }
  vector<Record> _dict;
};
int main() {
  Dictionary d;
  d.read("The_Holy_Bible.txt");
  d.store("dict.txt");
  return 0;
}
