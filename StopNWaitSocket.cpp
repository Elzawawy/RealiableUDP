//
// Created by zawawy on 5/9/19.
//

#include "StopNWaitSocket.h"
#include "SocketHelper.h"
#define MAXACKSIZE 50
#define MAXPKTSIZE 510
#define TIMEOUT_SECS 20

void StopNWaitSocket::Send(string &message) {
    //Break the message into an array of packets to be sent.
    vector<SocketHelper::Packet> packets;
    //State variable.
    int state = 0;
    int alternatebit =0;
    int numbytes;
    SocketHelper::AckPacket* ackpacket;
    string ackstring;
    for (SocketHelper::Packet pkt: packets) {
            udp_socket_.Send(*socket_helper_.PacketToString(pkt));
            while(true)
            {
                numbytes = udp_socket_.ReceiveTillTimeout(ackstring,MAXACKSIZE,TIMEOUT_SECS);
                if(numbytes == 0){
                    udp_socket_.Send(*socket_helper_.PacketToString(pkt));
                }
                else {
                    ackpacket = socket_helper_.StringToAckPacket(ackstring);
                    if (ackpacket->ackno == alternatebit) break;
                }
            }
            alternatebit = !alternatebit;
        }
}

void StopNWaitSocket::Receive(string &message, int max_length) {
    SocketHelper::Packet* packet;
    SocketHelper::AckPacket ackPacket(0, 0,0);
    string pktstring;
    int alternatebit = 0;
    int numbytes;
    while(true){
        numbytes = udp_socket_.ReceiveTillTimeout(pktstring,MAXPKTSIZE,TIMEOUT_SECS);
        if(numbytes == 0) break;
        else {
            packet = socket_helper_.StringToPacket(pktstring);
            message.append(*packet->data);
            if(packet->len < 500 || message.length() >= max_length) {break;}
            if(packet->seqno == alternatebit)
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(alternatebit));
            else
                ackPacket = SocketHelper::AckPacket(0, 0, static_cast<uint32_t>(!alternatebit));
            udp_socket_.Send(*socket_helper_.AckPacketToString(ackPacket));
        }
        alternatebit = !alternatebit;
    }

}
