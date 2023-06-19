#include "../../../include/Client_Socket.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Socket::Socket() {
  fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
  if (fd_ < 0) {
    perror("socket");
    return;
  }
}

Socket::Socket(int fd)
    : fd_(fd) {
}

Socket::~Socket() {
  close(fd_);
}

int Socket::fd() const {
  return fd_;
}

void Socket::ShutDownWrite() {
  // 关闭写端
  int ret = shutdown(fd_, SHUT_WR);
  if (ret) {
    perror("shutdown");
    return;
  }
}

void Socket::SetTcpNoDelay(bool on) {
  int optval = on ? 1 : 0;
  int ret = ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
  if (ret < 0) {
    perror("setsockopt");
    return;
  }
}
