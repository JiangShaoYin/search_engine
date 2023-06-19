#pragma once

#include "Client_NonCopyable.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

class Socket
: NonCopyable
{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int fd() const;
    void ShutDownWrite();
    void SetTcpNoDelay(bool on);

private:
    int fd_;
};
