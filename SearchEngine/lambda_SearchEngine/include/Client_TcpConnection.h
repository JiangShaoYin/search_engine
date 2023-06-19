#pragma once

#include "Client_Socket.h"
#include "Client_SocketIO.h"
#include "Client_InetAddress.h"

#include <memory>
#include <functional>

using std::shared_ptr;
using std::function;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void Send(const string &msg);
    void SendInt(int num);
    string Receive(int len);
    int ReceiveInt();
    bool IsClosed() const;
    //为了方便调试的函数
    string ToString();

    //注册Tcp连接中的三个事情
    void SetConnectionCallback(const TcpConnectionCallback &cb);
    void SetMessageCallback(const TcpConnectionCallback &cb);
    void SetCloseCallback(const TcpConnectionCallback &cb);

    //执行Tcp通信过程中的三个事件
    void HandleConnectionCallback();
    void HandleMessageCallback();
    void HandleCloseCallback();

private:
    //获取本端地址与对端地址
    InetAddress GetLocalAddr();
    InetAddress GetPeerAddr();

private:
    SocketIO sockIO_;

    //为了调试而加入的函数
    Socket sock_;
    InetAddress localAddr_;
    InetAddress peerAddr_;

    TcpConnectionCallback onConnectionCb_;//连接建立
    TcpConnectionCallback onMessageCb_;//消息到达
    TcpConnectionCallback onCloseCb_;//连接断开
};
