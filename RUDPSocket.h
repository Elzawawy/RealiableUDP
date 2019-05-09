//
// Created by zawawy on 5/7/19.
//

#ifndef RUDPSOCKET_H
#define RUDPSOCKET_H

#include <string>
#include <mutex>
#include <condition_variable>
#include "SocketHelper.h"
#include "Timer.h"
#include "UDPSocket.h"
#include "Socket.h"

using namespace std;

class RUDPSocket : Socket {
public:
    RUDPSocket(int send_maxsize,UDPSocket::ip_version version =ipv4,string ip_addr="",string port_num="");
    void Send(string& message) override;
    void Receive(string &message, int max_length) override;
    void* RetransmitPackets();

private:
    UDPSocket udp_socket_;
    SocketHelper socket_helper_ = SocketHelper(500);
    Timer timer_;
    vector<SocketHelper::Packet> *packets;
    //Make a initial packet to send when packet received is out of order.
    SocketHelper::AckPacket ack_packet_ = SocketHelper::AckPacket(0,0,0);
    void* sendpkt_th(SocketHelper::Packet &packet, int th_id);
    int base_;
    int next_seqnum_;
    int sendwind_size_;
    int expected_seqnum_;
    mutex mtx_;                 // mutex for critical section
    condition_variable run_cv_;  // condition variable for critical section
    condition_variable recv_run_;
    bool ready_run_ = false;
    int current_thid_ = 0;
    void* StartTimer(int timer_duration_ms_);
    void RunThreads();


};


#endif //REALIABLEUDP_RUDPSOCKET_H
