#include "../../../include/Client_TcpConnection.h"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd)
    : sockIO_(fd), sock_(fd), localAddr_(GetLocalAddr()), peerAddr_(GetPeerAddr()) {
}

TcpConnection::~TcpConnection() {
}

void TcpConnection::Send(const string &msg) {
  sockIO_.Writen(msg.c_str(), msg.size());
}

void TcpConnection::SendInt(int num) {
  sockIO_.Writen((char *)&num, sizeof(int));
}

string TcpConnection::Receive(int len) {
  char buff[len + 1] = {0};
  sockIO_.Readn(buff, len);

  return string(buff);
}

int TcpConnection::ReceiveInt() {
  int num;
  sockIO_.Readn((char *)&num, sizeof(int));
  return num;
}

// 查看对应的缓冲区中是否有数据
bool TcpConnection::IsClosed() const {
  char buf[10] = {0};
  int ret = ::recv(sock_.fd(), buf, sizeof(buf), MSG_PEEK);

  return 0 == ret;
}

string TcpConnection::ToString() {
  ostringstream oss;
  oss << localAddr_.Ip() << ":"
      << localAddr_.Port() << "---->"
      << peerAddr_.Ip() << ":"
      << peerAddr_.Port();

  return oss.str();
}

// 获取本端的网络地址信息
InetAddress TcpConnection::GetLocalAddr() {
  struct sockaddr_in addr;
  socklen_t len = sizeof(struct sockaddr);
  // 获取本端地址的函数getsockname
  int ret = getsockname(sock_.fd(), (struct sockaddr *)&addr, &len);
  if (-1 == ret) {
    perror("getsockname");
  }

  return InetAddress(addr);
}

// 获取对端的网络地址信息
InetAddress TcpConnection::GetPeerAddr() {
  struct sockaddr_in addr;
  socklen_t len = sizeof(struct sockaddr);
  // 获取对端地址的函数getpeername
  int ret = getpeername(sock_.fd(), (struct sockaddr *)&addr, &len);
  if (-1 == ret) {
    perror("getpeername");
  }

  return InetAddress(addr);
}

// 注册Tcp连接中的三个事情
void TcpConnection::SetConnectionCallback(const TcpConnectionCallback &cb) {
  onConnectionCb_ = cb;
}
void TcpConnection::SetMessageCallback(const TcpConnectionCallback &cb) {
  onMessageCb_ = cb;
}
void TcpConnection::SetCloseCallback(const TcpConnectionCallback &cb) {
  onCloseCb_ = cb;
}

// 执行Tcp通信过程中的三个事件
void TcpConnection::HandleConnectionCallback() {
  if (onConnectionCb_) {
    // 为了防止指针的误用，也就是防止不同的智能指针
    // 托管同一个裸指针
    /* _onConnectionCb(shared_ptr<TcpConnection>(this)); */
    onConnectionCb_(shared_from_this());
  }
}
void TcpConnection::HandleMessageCallback() {
  if (onMessageCb_) {
    onMessageCb_(shared_from_this());
  }
}
void TcpConnection::HandleCloseCallback() {
  if (onCloseCb_) {
    onCloseCb_(shared_from_this());
  }
}
