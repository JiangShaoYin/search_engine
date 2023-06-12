#include "../../../include/Client_Socket.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

Socket::Socket() {
  _fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (_fd < 0) {
    perror("socket");
    return;
  }
}

Socket::Socket(int fd)
    : _fd(fd) {
}

Socket::~Socket() {
  close(_fd);
}

int Socket::fd() const {
  return _fd;
}

void Socket::shutDownWrite() {
  // 关闭写端
  int ret = shutdown(_fd, SHUT_WR);
  if (ret) {
    perror("shutdown");
    return;
  }
}

void Socket::setTcpNoDelay(bool on) {
  int optval = on ? 1 : 0;
  int ret = ::setsockopt(_fd, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
  if (ret < 0) {
    perror("setsockopt");
    return;
  }
}
