#include "../../../include/Server_Acceptor.h"
#include <stdio.h>

Acceptor::Acceptor(const string &ip, unsigned short port)
: _sock()
, _addr(ip, port)
{
}

Acceptor::~Acceptor()
{

}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr()
{
    int on = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret)
    {
        perror("setsockopt");
        logError("Server_Acceptor::setReuseAddr()");
        return;
    }
}

void Acceptor::setReusePort()
{
    int on = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(-1 == ret)
    {
        perror("setsockopt");
        logError("Server_Acceptor::setReusePort()");
        return;
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(), 
                     (struct sockaddr *)_addr.getInetAddrPtr(),
                     sizeof(struct sockaddr));
    if(-1 == ret)
    {
        perror("bind");
        logError("Server_Acceptor::bind()");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(), 128);
    if(-1 == ret)
    {
        perror("listen");
        logError("Server_Acceptor::listen()");
        return;
    }
}

int Acceptor::accept()
{
    int connfd = ::accept(_sock.fd(), nullptr, nullptr);
    if(-1 == connfd)
    {
        perror("accept");
        logError("Server_Acceptor::accept()");
        return -1;
    }
    return connfd;
}

int Acceptor::fd() const
{
    return _sock.fd();
}

