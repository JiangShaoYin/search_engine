#include <iostream>
#include <vector>
using namespace std;

void swap(int & a, int & b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void print(vector<int> & v) {
    cout << "v = {";
    for(auto & ele : v){
        cout << ele << " ";
    }
    cout << "}" << endl;
}

void seperate(vector<int> & v) {
    int e = v.size() - 1;
    for(int i = 0; i < v.size(); ++i) {
        while(v[i] % 2 == 0 && i < e) {
            swap(v[i], v[e]);
            --e;
        }
    }
}

int main(){
    vector<int> v = {2,2,2};
    seperate(v);
    print(v);
    return 0;
}
