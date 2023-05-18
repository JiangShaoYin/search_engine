#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main() {
  list<int> lst;
  list<int>::iterator iter1 = lst.begin(), iter2 = lst.end();
  // 以下代码报错原因为：list::iterator 不支持 < 操作
//   while (iter1 < iter2) {
//     //....
//   }
  return 0;
}
