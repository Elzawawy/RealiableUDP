//
// Created by zawawy on 5/1/19.
//
#include "Socket.h"
#include <sys/socket.h>
#ifndef RUDP_UDPSOCKET_H
#define RUDP_UDPSOCKET_H

#include <string>
using namespace std;
class UDPSocket : public Socket{

public:
    typedef enum ip_version { ipv4=AF_INET,ipv6=AF_INET6,unspecified=AF_UNSPEC}ip_version;
    UDPSocket(ip_version version,string ip_addr="",string port_num="");
    void Send();
    void Receive(string &message, int max_length);
private:
    struct addrinfo *results_;
    int sock_fd_;
    sockaddr* addr_;
    socklen_t addr_len_;
};


#endif //RUDP_UDPSOCKET_H
