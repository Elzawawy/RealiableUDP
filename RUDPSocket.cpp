//
// Created by zawawy on 5/7/19.
//

#include <vector>
#include <thread>
#include "UDPSocket.h"
#include "RUDPSocket.h"



void RUDPSocket::Send(string& message) {
    //Break the message into an array of packets to be sent.
    packets=socket_helper_.MakePackets(message,0);
    vector<string> Acks(packets->size());


    int th_id = 0;
    for (SocketHelper::Packet pkt: *packets) {
        //create a thread for each packet.
        thread th(&RUDPSocket::sendpkt_th,this,pkt, th_id);
        //detach the thread from main thread.
        th.detach();
        //increment thread id.
        th_id ++;
    }
    RunThreads();
    /*Receiving the acks*/
    for (int i = 0; i < packets->size(); ++i) {
        udp_socket_.Receive(Acks[i],64);
        base_=socket_helper_.StringToAckPacket(Acks[i])->ackno+1;
        if(base_==next_seqnum_){
            //stop timer
            timer_.StopTimer();
        }else{
            /*passing the retransmit packets as a callback and this object as a parameter*/
            timer_.StartTimer(&RUDPSocket::RetransmitPackets,this);
        }

    }




}
void RUDPSocket::RunThreads(){
    std::unique_lock<std::mutex> lck(this->mtx_);
    ready_run_= true;
    run_cv_.notify_all();
}

void RUDPSocket::Receive(string &message, int max_length) {
    sockaddr_storage storage{};
    //Receive an unreliable message.
    udp_socket_.Receive(message,max_length,storage);
    //convert this string into packet format.
    SocketHelper::Packet * rcvpkt = socket_helper_.StringToPacket(message);
    //if it has the expected sequence number.
    if(rcvpkt->seqno == expected_seqnum_)
    {
        //extract and deliver data.
        message = *rcvpkt->data;
        //prepare ack packet.
        ack_packet_ = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(expected_seqnum_));
        //increment expected sequence number.
        expected_seqnum_++;
    }
    //send the ack packet whether an updated version of it or the oldest ACK available.
    udp_socket_.Send(*socket_helper_.AckPacketToString(ack_packet_),storage);
}

RUDPSocket::RUDPSocket(int send_maxsize,UDPSocket::ip_version version,string ip_addr,string port_num):timer_(20),udp_socket_(version, ip_addr, port_num) {

    // Initialize variables used in GBN.
    this->base_ = 1;
    this->next_seqnum_ = 1;
    this->expected_seqnum_ = 1;
    // Initialize Sending sliding window maximum size.
    this->sendwind_size_ = send_maxsize;

}

void *RUDPSocket::sendpkt_th(SocketHelper::Packet packet, int th_id) {
    std::unique_lock<std::mutex> lock(mtx_);
    while(th_id != current_thid_ || !ready_run_ )
        run_cv_.wait(lock);
    current_thid_++;
    if(next_seqnum_ < base_ + sendwind_size_)
    {
        udp_socket_.Send(*(socket_helper_.PacketToString(packet)));
        if(base_ == next_seqnum_)
           timer_.StartTimer(&RUDPSocket::RetransmitPackets,this);
        next_seqnum_++;
    }
    return nullptr;
}



void *RUDPSocket::RetransmitPackets() {
    timer_.StartTimer(&RUDPSocket::RetransmitPackets,this);
    for (int i=base_;i<next_seqnum_;i++) {
        udp_socket_.Send(*socket_helper_.PacketToString((*packets)[i]));
    }
    return nullptr;
}

void RUDPSocket::Receive(string &message, int max_length, sockaddr_storage& storage) {

    //Receive an unreliable message.
    udp_socket_.Receive(message,max_length,storage);
    //convert this string into packet format.
    SocketHelper::Packet * rcvpkt = socket_helper_.StringToPacket(message);
    //if it has the expected sequence number.
    if(rcvpkt->seqno == expected_seqnum_)
    {
        //extract and deliver data.
        message = *rcvpkt->data;
        //prepare ack packet.
        ack_packet_ = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(expected_seqnum_));
        //increment expected sequence number.
        expected_seqnum_++;
    }
    //send the ack packet whether an updated version of it or the oldest ACK available.
    udp_socket_.Send(*socket_helper_.AckPacketToString(ack_packet_),storage);

}

void RUDPSocket::Send(string &message, sockaddr_storage& storage) {

        //Break the message into an array of packets to be sent.
        packets=socket_helper_.MakePackets(message,base_);
        vector<string> Acks(packets->size());


        int th_id = 0;
        for (SocketHelper::Packet pkt: *packets) {
            //create a thread for each packet.
            thread th(&RUDPSocket::sendpkt_To_th,this,pkt, th_id,storage);
            //detach the thread from main thread.
            th.detach();
            //increment thread id.
            th_id ++;
        }
        RunThreads();
        /*Receiving the acks*/
        for (int i = 0; i < packets->size(); ++i) {
            udp_socket_.Receive(Acks[i],64);
            base_=socket_helper_.StringToAckPacket(Acks[i])->ackno+1;
            if(base_==next_seqnum_){
                //stop timer
                timer_.StopTimer();
            }else{
                /*passing the retransmit packets as a callback and this object as a parameter*/
                timer_.StartTimer(&RUDPSocket::RetransmitPackets,this);
            }

        }




    }


void *RUDPSocket::sendpkt_To_th(SocketHelper::Packet packet, int th_id, sockaddr_storage storage) {
    std::unique_lock<std::mutex> lock(mtx_);
    while(th_id != current_thid_ || !ready_run_ )
        run_cv_.wait(lock);
    current_thid_++;
    if(next_seqnum_ < base_ + sendwind_size_)
    {
        udp_socket_.Send(*(socket_helper_.PacketToString(packet)),storage);
        if(base_ == next_seqnum_)
            timer_.StartTimer(&RUDPSocket::RetransmitPackets,this);
        next_seqnum_++;
    }
    return nullptr;
}




