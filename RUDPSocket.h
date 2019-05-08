//
// Created by zawawy on 5/7/19.
//

#ifndef RUDPSOCKET_H
#define RUDPSOCKET_H

#include <string>
#include <mutex>
#include <condition_variable>
#include "UDPSocket.h"
#include "Socket.h"

using namespace std;

class RUDPSocket : Socket {
public:
    RUDPSocket(UDPSocket::ip_version version,string ip_addr="",string port_num="",int send_maxsize=0);
    void Send(string& message) override;
    void Receive(string &message, int max_length) override;

private:
    UDPSocket udp_socket_;
    void* sendpkt_th(Packet &packet, int th_id);
    int base_;
    int next_seqnum_;
    int sendwind_size_;
    mutex mtx_;                 // mutex for critical section
    condition_variable run_cv_;  // condition variable for critical section
    condition_variable recv_run_;
    bool ready_run_ = false;
    int current_thid_ = 0;
};


#endif //REALIABLEUDP_RUDPSOCKET_H
