#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
    map<string, int> testInt;
    cout << testInt["test"] << endl;
    map<string, set<int> > testSet;
    testSet["test"].insert(1);
    cout << testSet["test"].size() << endl;
    return 0;
}