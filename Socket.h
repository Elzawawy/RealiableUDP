//
// Created by zawawy on 5/1/19.
//

#ifndef SOCKET_H
#define SOCKET_H

#include <string.h>

using namespace std;
class Socket {
public:
    virtual void Send(string &message) = 0;
    virtual void Receive(string &message, int max_length) = 0;
};


#endif //RUDP_SOCKET_H
