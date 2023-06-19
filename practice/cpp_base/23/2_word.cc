#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将所有单词放入词典
        unordered_set<string> word_set (wordList.begin(), wordList.end());
        // 如果词典中没有结尾词，永远无法完成目标
        if(!word_set.count(endWord)) return 0;
        unordered_map<string,int> word_cnt {{beginWord,1}};
        queue<string> q ({beginWord}); 
        // 从第一个词开始广度搜索
        while(!q.empty()) {
            // 取出第一个词
            string word = q.front();
            q.pop();
            // 依次排查第一个词的每一位
            for(int i = 0; i < word.size(); ++i) {
                string tmpword = word;
                // 遍历每个字母，查看其是否在字典里
                for(char ch = 'a'; ch <= 'z'; ++ch) {
                    tmpword[i] = ch;
                    // 如果在词典里有，且是结尾词，就直接返回
                    if(word_set.count(tmpword) && tmpword == endWord) return word_cnt[word] + 1;
                    // 如果在词典里有，但不是结尾词，并且现在map中还没有这个单词
                    // 就说明这个单词之前还没有被记录过，当前就是到这个单词的最短路径
                    // 入队列，并且入map，此时到这个单词的最短距离就是上个单词最短距离 + 1
                    if(word_set.count(tmpword) && !word_cnt.count(tmpword)) {
                        q.push(tmpword);
                        word_cnt[tmpword] = word_cnt[word] + 1;
                    }
                    // 如果单词在词典里有，map中也有，说明之前到过这里，这次到这个单词不是最短距离，就不用记录
                    // 如果单词不在词典里，更不用记录了
                }
            }
        }
        return 0;
    }
};
