#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "log4pp.h"
#include "Server_Socket.h"
#include "Server_InetAddress.h"
#include <string>

using std::string;

class Acceptor
{
public:
    Acceptor(const string &ip, unsigned short port);
    ~Acceptor();
    void ready();
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
    int accept();
    int fd() const;

private:
    Socket _sock;
    InetAddress _addr;
};

#endif

