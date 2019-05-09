//
// Created by zawawy on 5/1/19.
//
#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Socket.h"
#include <string>
using namespace std;
class UDPSocket : public Socket{

public:
    UDPSocket(ip_version version,string ip_addr="",string port_num="");
    UDPSocket();
    void Send(string &message);
    void Receive(string &message, int max_length);
    int  ReceiveTillTimeout(string &message, int max_length, int timeout);
    int  ReceiveAll(string &message, int max_length, int timeout);
private:
    struct addrinfo *results_;
    int sock_fd_;
    sockaddr* addr_;
    socklen_t addr_len_;
};


#endif //RUDP_UDPSOCKET_H
