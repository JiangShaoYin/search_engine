#pragma once
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include "Client_Socket.h"
#include "Client_InetAddress.h"
#include "Client_SocketIO.h"
#include "Client_TcpConnection.h"
#include "Client_InetAddress.h"
#include <nlohmann/json.hpp>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::vector;
using json = nlohmann::json;
struct Page {
  int id;
  string summary;
  string title;
  string url;
};
class Client {
public:
    Client(const string &ip, unsigned short port);
    ~Client();
    void Connect(); // 连接服务器，获取赋值后的sockfd
    void Start(); // 启动客户端
    void AddEpollReadFd(int fd); // 将文件描述符放在红黑树上进行监听
    string ReadStdin(); // 从标准输入读取数据
    void SendServer(string msg, TcpConnection & con); // 向服务器发送数据
    string ReadServer(TcpConnection & con); // 从服务器读取数据
    void DisplayKey(string result); // 显示服务器发送的数据
    void DisplayWeb(string result);
    void PagingDisplay(vector<Page> &v);
    void Close(); // 关闭客户端
    int CreateEpollFd(); // 创建epfd文件描述符
private:
    int epfd_; // epoll_create返回的文件描述符
    Socket sock_; // 储存本地的socket，其中包含sockfd
    bool isClosed_; // 标记客户端是否关闭
    InetAddress addr_; // 服务器的地址信息
};