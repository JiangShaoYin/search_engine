#include <iostream>
#include <vector>
#include <map>
using namespace std;

int moreThanHalfValue(vector<int> &numbers){
    if(numbers.size() == 0){
        return 0;
    }
    map<int,int> count;
    for(auto & ele : numbers){
        count[ele]++;
    }
    for(auto & ele : count) {
        if(ele.second > numbers.size() / 2){
            return ele.first;
        }
    }
    return 0;
}

int main() {
    vector<int> numbers = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    cout << moreThanHalfValue(numbers) << endl;
    return 0;
}