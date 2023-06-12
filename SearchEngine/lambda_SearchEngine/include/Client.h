#ifndef __CLIENT_H__
#define __CLIENT_H__

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
    void connect(); // 连接服务器，获取赋值后的sockfd
    void start(); // 启动客户端
    void addEpollReadFd(int fd); // 将文件描述符放在红黑树上进行监听
    string readStdin(); // 从标准输入读取数据
    void sendServer(string msg, TcpConnection & con); // 向服务器发送数据
    string readServer(TcpConnection & con); // 从服务器读取数据
    void displayKey(string result); // 显示服务器发送的数据
    void displayWeb(string result);
    void pagingDisplay(vector<Page> &v);
    void close(); // 关闭客户端
    int createEpollFd(); // 创建epfd文件描述符
private:
    int _epfd; // epoll_create返回的文件描述符
    Socket _sock; // 储存本地的socket，其中包含sockfd
    bool _isClosed; // 标记客户端是否关闭
    InetAddress _addr; // 服务器的地址信息
};

#endif
