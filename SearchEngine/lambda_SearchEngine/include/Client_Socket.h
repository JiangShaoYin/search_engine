#ifndef __SOCKET_H__
#define __SOCKET_H__

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
    void shutDownWrite();
    void setTcpNoDelay(bool on);

private:
    int _fd;
};

#endif
