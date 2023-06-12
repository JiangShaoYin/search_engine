#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "Server_NonCopyable.h"
#include "log4pp.h"

class Socket
: NonCopyable
{
public:
    Socket();
    explicit Socket(int fd);
    ~Socket();
    int fd() const;
    void shutDownWrite();

private:
    int _fd;
};

#endif

