//
// Created by zawawy on 5/9/19.
//


#ifndef STOPNWAITSOCKET_H
#define STOPNWAITSOCKET_H

#include <string>
#include "Socket.h"
#include "UDPSocket.h"
#include "SocketHelper.h"

using namespace std;

class StopNWaitSocket : Socket{

    void Send(string &message) override;

    void Receive(string &message, int max_length) override;

private:
    UDPSocket udp_socket_;
    SocketHelper socket_helper_ = SocketHelper(500);

};


#endif //REALIABLEUDP_STOPNWAITSOCKET_H
