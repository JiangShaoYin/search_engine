#ifndef _WEBPAGESEARCHER_H_
#define _WEBPAGESEARCHER_H_
#include <string>
#include <memory>
#include "Server_TcpConnection.h"
#include "WebPageQuery.h"

using std::string;
using std::shared_ptr;

class WebPageSearcher {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
public:
    WebPageSearcher(const string &sought);
    ~WebPageSearcher();
    string doQuery(const string &str);

private:
string _sought;
WebPageQuery _query;
};

#endif
