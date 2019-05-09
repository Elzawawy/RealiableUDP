//
// Created by zawawy on 5/1/19.
//

#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>
#include <sys/socket.h>

using namespace std;

class Socket {
public:
    typedef enum ip_version { ipv4=AF_INET,ipv6=AF_INET6,unspecified=AF_UNSPEC}ip_version;
    virtual void Send(string &message) = 0;
    virtual void Receive(string &message, int max_length) = 0;
};


#endif //RUDP_SOCKET_H
