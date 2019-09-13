//
// Created by zawawy on 5/9/19.
//


#ifndef STOPNWAITSOCKET_H
#define STOPNWAITSOCKET_H

#include <string>
#include "../../abstract_sockets/Socket.h"
#include "../../unreliable_sockets/UDPSocket.h"
#include "../../utils/SocketHelper.h"
#define PROBABILITY_OF_LOSS 0

using namespace std;

class StopNWaitSocket : Socket{
public:
    StopNWaitSocket(ip_version version=ipv4,string ip_addr="",string port_num="");
    void Send(string &message) override;
    void Receive(string &message, int max_length) override;
    void Send(string &message, struct sockaddr_storage storage) override;
    void Receive(string &message, int max_length, struct sockaddr_storage &storage) override;
private:
    UDPSocket udp_socket_;
    SocketHelper socket_helper_ = SocketHelper(500);

};


#endif //REALIABLEUDP_STOPNWAITSOCKET_H
