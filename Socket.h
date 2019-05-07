//
// Created by zawawy on 5/1/19.
//

#ifndef RUDP_SOCKET_H
#define RUDP_SOCKET_H


class Socket {
public:
    virtual void Send() = 0;
    virtual void Receive() = 0;
};


#endif //RUDP_SOCKET_H
