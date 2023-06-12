#include "../../../include/Server_TcpConnection.h"
#include "../../../include/Server_EventLoop.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd, EventLoop *loop)
: _loop(loop)
, _sockIO(fd)
, _sock(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::send(const string &msg)
{
    int len = msg.size();
    // cout << "before send len : " << len << endl;
    _sockIO.writen((char*)&len, sizeof(int));
    // cout << "after send len : " << len << endl;
    // cout << "before send msg : " << msg << endl;
    _sockIO.writen(msg.c_str(), msg.size());
    // cout << "after send msg : " << msg << endl;
}

void TcpConnection::sendInLoop(const string &msg)
{
    if(_loop)
    {
        //将线程池处理好之后的msg，以及发送msg的能力，也就是
        //TcpConnection中的send方法都交给了EventLoop，然后
        //在EventLoop里面再去发送数据给客户端
        // cout << "TcpConnection::sendInLoop... msg : " << msg << endl;
        _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff, sizeof(buff));

    return string(buff);
}

int TcpConnection::receiveInt()
{
    int num;
    _sockIO.readn((char *)&num,sizeof(int));
    return num;
}

//查看对应的缓冲区中是否有数据
bool TcpConnection::isClosed() const
{
    char buf[10] = {0};
    int ret = ::recv(_sock.fd(), buf, sizeof(buf), MSG_PEEK);

    return 0 == ret;
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getsockname");
        logError("Server_TcpConnection::getLocalAddr()");
    }

    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr );
    //获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if(-1 == ret)
    {
        perror("getpeername");
        logError("Server_TcpConnection::getPeerAddr()");
    }

    return InetAddress(addr);
}

//注册Tcp连接中的三个事情
void TcpConnection::setConnectionCallback(const TcpConnectionCallback &cb)
{
    _onConnectionCb = cb;
}
void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessageCb = cb;
}
void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onCloseCb = cb;
}

//执行Tcp通信过程中的三个事件
void TcpConnection::handleConnectionCallback()
{
    if(_onConnectionCb)
    {
        //为了防止指针的误用，也就是防止不同的智能指针
        //托管同一个裸指针
        /* _onConnectionCb(shared_ptr<TcpConnection>(this)); */
        _onConnectionCb(shared_from_this());
    }
}
void TcpConnection::handleMessageCallback()
{
    if(_onMessageCb)
    {
        _onMessageCb(shared_from_this());
    }
}
void TcpConnection::handleCloseCallback()
{
    if(_onCloseCb)
    {
        _onCloseCb(shared_from_this());
    }
}

