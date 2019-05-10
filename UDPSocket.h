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
    UDPSocket(ip_version version=ipv4,string ip_addr="",string port_num="");
    UDPSocket();
    void Send(string &message);
    void Send(string &message,struct sockaddr_storage storage);
    void Receive(string &message, int max_length);
    void Receive(string &message, int max_length,struct sockaddr_storage &storage);
    int  ReceiveTillTimeout(string &message, int max_length, int timeout);
    int  ReceiveTillTimeout(string &message, int max_length, int timeout,struct sockaddr_storage &storage);
private:
    struct addrinfo *results_;
    int sock_fd_;
    sockaddr* addr_;
    socklen_t addr_len_;
};


#endif //RUDP_UDPSOCKET_H
