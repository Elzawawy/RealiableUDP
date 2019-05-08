//
// Created by zawawy on 5/1/19.
//
#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Socket.h"
#include <sys/socket.h>
#include <string>
using namespace std;
class UDPSocket : public Socket{

public:
    typedef enum ip_version { ipv4=AF_INET,ipv6=AF_INET6,unspecified=AF_UNSPEC}ip_version;
    UDPSocket(ip_version version,string ip_addr="",string port_num="");
    UDPSocket();
    void Send(string &message);
    void Receive(string &message, int max_length);
private:
    struct addrinfo *results_;
    int sock_fd_;
    sockaddr* addr_;
    socklen_t addr_len_;
};


#endif //RUDP_UDPSOCKET_H
