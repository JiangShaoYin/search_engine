#include "../../../include/WebPageSearcher.h"
#include "../../../include/WebPageQuery.h"
#include "../../../include/Configuration.h"
#include "../../../include/CppJieba.h"
#include "../../../include/log4pp.h"

#include <iostream>


using std::cout;
using std::endl;

WebPageSearcher::WebPageSearcher(const string & sought)
    : sought_(sought)
    { 
        // 日志信息===================================
        logInfo("网页查询 - 初始化查询器WebPageSearcher");

    }

WebPageSearcher::~WebPageSearcher() { }

string WebPageSearcher::doQuery(const string & str) {
    // 日志信息===================================
    logInfo("网页查询 - WebPageSearcher::开始查询");
    string result = query_.DoQuery(str);
    return result;
}
