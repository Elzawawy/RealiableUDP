//
// Created by zawawy on 5/7/19.
//

#include <vector>
#include <thread>
#include "RUDPSocket.h"



void RUDPSocket::Send(string& message) {
    //Break the message into an array of packets to be sent.
    vector<Packet> packets;
    for (Packet pkt: packets) {
        //create a thread for each packet.
        thread th(&RUDPSocket::sendpkt_th,this, pkt);
        //detach the thread from main thread.
        th.detach();
    }




}

void RUDPSocket::Receive(string &message, int max_length) {

}

RUDPSocket::RUDPSocket(int send_maxsize) {

    // Initialize variables used in GBN.
    this->base_ = 1;
    this->next_seq_num_ = 1;
    // Initialize Sending sliding window maximum size.
    this->sendwind_size_ = send_maxsize;
}

void *RUDPSocket::sendpkt_th(RUDPSocket::Packet &packet, int th_id) {
    std::unique_lock<std::mutex> lock(mtx_);
    while(th_id != current_thid_ || !ready_run_ )
        run_cv_.wait(lock);

    return nullptr;
}
