#include <iostream>
#include <vector>
#include <set>
using namespace std;
/*
题目：缺失的第一个正数
给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
*/

int firstMissingPositive(vector<int> & v) {
    int n = v.size();
    for(int i = 0; i < n; ++i) {
        while(v[i] > 0 && v[i] <= n && v[v[i] - 1] != v[i]) {
            swap(v[i], v[v[i] - 1]);
        }
    }
    for(int i = 0; i < n; ++i) {
        if(v[i] != i + 1) {
            return i + 1;
        }
    }
    return n + 1;
}

int test(vector<int> & v) {
    set<int> s;
    for(auto & ele : v) {
        s.insert(ele);
    }
    int res = 1;
    for(auto & ele : s) {
        if(ele == res) {
            ++res;
        }
    }
    return res;
}

int main() {
    vector<int> v = {1,3,4,8,2};
    cout << "res is " << test(v) << endl;
    return 0;
}