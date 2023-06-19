#pragma once
#include <arpa/inet.h>
#include <string>

using std::string;

class InetAddress
{
public:
    InetAddress(const string &ip, unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();
    string Ip() const;
    unsigned short Port() const;
    const struct sockaddr_in *GetInetAddrPtr() const;

private:
    struct sockaddr_in addr_;

};