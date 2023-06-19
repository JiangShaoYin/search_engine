#pragma once

#include <memory>
#include <string>

#include "Server_TcpConnection.h"
#include "WebPageQuery.h"

using std::shared_ptr;
using std::string;

class WebPageSearcher {
  using TcpConnectionPtr = shared_ptr<TcpConnection>;

 public:
  WebPageSearcher(const string &sought);
            
  ~WebPageSearcher();
  string doQuery(const string &str);

 private:
  string sought_;
  WebPageQuery query_;
};
