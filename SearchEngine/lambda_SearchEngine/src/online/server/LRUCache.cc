#include "../../../include/LRUCache.h"
#include "../../../include/log4pp.h"
#include<sstream>
#include<fstream>

using namespace std;

string LRUCache::get(string query){
    if(_cache.count(query)==0){
        //cout<<"get NULL"<<endl;
        return "";
    } else {
        auto it = _cache[query];
        auto tmp = *it;//保存队列元素的值
        // cout<<(*it).first<<endl;
        string res = tmp.second;//返回队列元素的值
        _dlist.erase(it);//删除队列元素
        _dlist.push_front(tmp);//把元素插入队列头
        it = _dlist.begin();
        _cache[query] = it;
        cout<<"_pendsize()"<<_pendingUpdateList.size()<<endl;
        if(_pendingUpdateList.find(query)!=_pendingUpdateList.end()){
            cout<<res<<endl;
            return res;
        }else{
            if(_pendingUpdateList.size()<_pendingcap){
                _pendingUpdateList[query]=tmp;
            }
        }
        cout<<"res"<<res<<endl;
          
        return res;
        
    }
}


int LRUCache::put(string query,string recommand){
        _pendingUpdateList[query]=make_pair(query,recommand);
        if(_pendingUpdateList.size()>_pendingcap){
            _pendingUpdateList.erase(query);
            return 0;
        }
        _dlist.push_front(make_pair(query,recommand));
        auto it = _dlist.begin();
    
        _cache[query] = it;
        if(_dlist.size() > _capacity){
            auto tmp = _dlist.back();
            _cache.erase(tmp.first);
            _dlist.pop_back();    
        } 
    return 0; 
}

int LRUCache::readToFile(const string & filename){
     // 创建一个名为 "example.txt" 的输入文件流（ifstream）对象
    std::ifstream LruIn(filename);

    // 检查文件是否成功打开
    if (!LruIn) {
        cerr << "Error: Cannot open the file." << endl;
        return 1;
    }

    string line;
    
    // 使用 getline 函数逐行读取文件内容
    while (getline(LruIn, line)) {
        // 使用istringstream将字符串视为输入流
        istringstream line_stream(line);
        
        string word;
        line_stream >> word;
        string wordtemp=word;
        string keytemp=line_stream.str().substr(word.size() + 1);
        // 使用 >> 运算符从字符串流中逐词读取
        
        pair<string,string> pairtemp={wordtemp,keytemp};
        _dlist.push_front(pairtemp);
         //_cache.insert(make_pair(wordtemp,_dlist.back()));
        _cache[wordtemp] = _dlist.begin();

    
    }
    // 关闭文件
    LruIn.close();

    return 0;
}

int LRUCache::writeToFile(const string & filename)
{
    
    std::ofstream LruOut(filename);
    if(!LruOut.good()){
        cerr << "fstream is corrupted!" << endl;
        return -1;
    }
    for(auto pairtemp:_dlist){
        LruOut << pairtemp.first  << " "
               << pairtemp.second << endl;
    }
    LruOut.close();
    return 0;
}

mypair LRUCache::getpair(){
    mypair temppair;
    if(_pendingUpdateList.size()==0){
        temppair.first = "";
        temppair.second = "";
        return temppair; 
    }

    auto temp =_pendingUpdateList.begin()->second;
    temppair.first = temp.first;
    temppair.second = temp.second;
    _pendingUpdateList.erase(_pendingUpdateList.begin());
    return temppair;
}

void LRUCache::clear(){
    _pendingUpdateList.clear();
}

void LRUCache::putpair(mypair temp){
    // _pendingUpdateList.insert(make_pair(pairtemp.first,pairtemp));
    auto query=temp.first;
    auto recommand=temp.second;
    if(_cache.count(query)){
        auto it = _cache[query];

        _dlist.erase(it);

        _dlist.push_front(make_pair(query,recommand));

        it = _dlist.begin();

        //_cache.emplace(query,it);
        _cache[query] = it;
    } else {
        
        _dlist.push_front(make_pair(query,recommand));
        auto it = _dlist.begin();
        _cache[query] = it;
        if(_dlist.size() > _capacity){
            auto tmp = _dlist.back();
            _cache.erase(tmp.first);
            _dlist.pop_back();    
        } 
    }
    
}

void LRUCache::show(){
    cout<<"_pendlist: ";
    for(auto ch:_pendingUpdateList){
        cout<<ch.first<<" "<<ch.second.first<<" "<<ch.second.second<<"    ";
    }
    cout<<endl;
    
    cout<<"_dlist: ";
    for(auto ch:_dlist){
        cout<<ch.first<<" "<<ch.second<<"    ";
    }
    cout<<endl;
    
    cout<<"_cache: ";
    for(auto ch:_cache){
        cout<<ch.first<<" ";
        // <<ch.second.first<<" "<<ch.second.second<<"    ";
    }
    cout<<endl;
    
}
