//
// Created by zawawy on 5/9/19.
//
#include <iostream>
#include "Socket.h"
#include "UDPSocket.h"
#include "StopNWaitSocket.h"
#include "SocketHelper.h"
#define MAXACKSIZE 50
#define MAXPKTSIZE 508
#define TIMEOUT_SECS 20

void StopNWaitSocket::Send(string &message) {
    //Break the message into an array of packets to be sent.
    vector<SocketHelper::Packet> *packets = socket_helper_.MakePackets(message,1);
    //State variable.
    int state = 0;
    int alternatebit =0;
    int numbytes;
    SocketHelper::AckPacket* ackpacket;
    auto *ackstring = new string;
    cout<<"Start sending packets..."<<endl;
    for (SocketHelper::Packet pkt: *packets) {
        udp_socket_.Send(*socket_helper_.PacketToString(pkt));
        while(true)
        {
            cout<<"Wait for ACK..."<<endl;
            numbytes = udp_socket_.ReceiveTillTimeout(*ackstring,MAXACKSIZE,TIMEOUT_SECS);
            if(numbytes == 0){
                cout<<"Time ran out ! Retransmitting packet..."<<endl;
                udp_socket_.Send(*socket_helper_.PacketToString(pkt));
            }
            else {
                cout<<"ACK Received"<<endl;
                string string1(&(*ackstring)[0]);
                ackpacket = socket_helper_.StringToAckPacket(string1);
                if (ackpacket->ackno == alternatebit) break;
            }
        }
        alternatebit = !alternatebit;
    }
}

void StopNWaitSocket::Receive(string &message, int max_length) {
    SocketHelper::Packet* packet;
    SocketHelper::AckPacket ackPacket(0, 0,0);
    struct sockaddr_storage storage;
    auto *pktstring = new string;
    int alternatebit = 0;
    int numbytes;
    while(true){
        cout<<"Waiting to receive any data..."<<endl;
        numbytes = udp_socket_.ReceiveTillTimeout(*pktstring,MAXPKTSIZE,TIMEOUT_SECS,storage);
        if(numbytes == 0) break;
        else {
            cout<<"Data Received."<<endl;
            //cout<<"check :==================\n"<<(*pktstring)[0]<<endl;
            string string1(&(*pktstring)[0]);
            //cout<<"======================="<<endl<<string1<<endl<<"====================================";
            packet = socket_helper_.StringToPacket(string1);
            message.append(*packet->data);
            if(packet->seqno == alternatebit)
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(alternatebit));
            else
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(!alternatebit));
            cout<<"Sending an ACK Packet..."<<endl;
            udp_socket_.Send(*socket_helper_.AckPacketToString(ackPacket),storage);
            if(packet->len < 500 || message.length() >= max_length) {break;}
        }
        alternatebit = !alternatebit;
    }

}

StopNWaitSocket::StopNWaitSocket(Socket::ip_version version, string ip_addr, string port_num) :udp_socket_(version,ip_addr,port_num) {}

void StopNWaitSocket::Send(string &message, struct sockaddr_storage storage) {
    //Break the message into an array of packets to be sent.
    vector<SocketHelper::Packet> *packets = socket_helper_.MakePackets(message,1);
    //State variable.
    int state = 0;
    int alternatebit =0;
    int numbytes;
    SocketHelper::AckPacket* ackpacket;
    auto *ackstring = new string;
    for (SocketHelper::Packet pkt: *packets) {
        udp_socket_.Send(*socket_helper_.PacketToString(pkt),storage);
        while(true)
        {
            numbytes = udp_socket_.ReceiveTillTimeout(*ackstring,MAXACKSIZE,TIMEOUT_SECS);
            if(numbytes == 0){
                udp_socket_.Send(*socket_helper_.PacketToString(pkt),storage);
            }
            else {
                string string1(&(*ackstring)[0]);
                ackpacket = socket_helper_.StringToAckPacket(string1);
                if (ackpacket->ackno == alternatebit) break;
            }
        }
        alternatebit = !alternatebit;
    }

}

void StopNWaitSocket::Receive(string &message, int max_length, struct sockaddr_storage &storage) {
    SocketHelper::Packet* packet;
    SocketHelper::AckPacket ackPacket(0, 0,0);
    auto *pktstring = new string;
    int alternatebit = 0;
    int numbytes;
    while(true){
        numbytes = udp_socket_.ReceiveTillTimeout(*pktstring,MAXPKTSIZE,TIMEOUT_SECS,storage);
        if(numbytes == 0) break;
        else {
            string string1(&(*pktstring)[0]);
            packet = socket_helper_.StringToPacket(string1);
            message.append(*packet->data);
            if(packet->seqno == alternatebit)
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(alternatebit));
            else
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(!alternatebit));
            udp_socket_.Send(*socket_helper_.AckPacketToString(ackPacket),storage);
            if(packet->len < 500 || message.length() >= max_length) {break;}
        }
        alternatebit = !alternatebit;
    }
}


