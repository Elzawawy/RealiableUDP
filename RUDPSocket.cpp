//
// Created by zawawy on 5/7/19.
//

#include <vector>
#include <thread>
#include "UDPSocket.h"
#include "RUDPSocket.h"



void RUDPSocket::Send(string& message) {
    //Break the message into an array of packets to be sent.
    vector<SocketHelper::Packet> packets;
    int th_id = 0;
    for (SocketHelper::Packet pkt: packets) {
        //create a thread for each packet.
        thread th(&RUDPSocket::sendpkt_th,this, th_id,pkt);
        //detach the thread from main thread.
        th.detach();
        //increment thread id.
        th_id ++;
    }




}

void RUDPSocket::Receive(string &message, int max_length) {

}

RUDPSocket::RUDPSocket(UDPSocket::ip_version version,string ip_addr,string port_num,int send_maxsize) {

    // Initialize variables used in GBN.
    this->base_ = 1;
    this->next_seqnum_ = 1;
    // Initialize Sending sliding window maximum size.
    this->sendwind_size_ = send_maxsize;
    this->udp_socket_ = UDPSocket(version, ip_addr, port_num);
    this->timer_ = Timer();
}

void *RUDPSocket::sendpkt_th(SocketHelper::Packet &packet, int th_id) {
    std::unique_lock<std::mutex> lock(mtx_);
    while(th_id != current_thid_ || !ready_run_ )
        run_cv_.wait(lock);
    current_thid_++;
    if(next_seqnum_ < base_ + sendwind_size_)
    {
        udp_socket_.Send(*(packet.data));
        if(base_ == next_seqnum_)
            timer_.StartTimer();
        next_seqnum_++;
    }
}

