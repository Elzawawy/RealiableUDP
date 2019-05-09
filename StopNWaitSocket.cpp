//
// Created by zawawy on 5/9/19.
//

#include "StopNWaitSocket.h"
#include "SocketHelper.h"

void StopNWaitSocket::Send(string &message) {
    //Break the message into an array of packets to be sent.
    vector<SocketHelper::Packet> packets;
    for (SocketHelper::Packet pkt: packets) {
        udp_socket_.Send(*socket_helper_.PacketToString(pkt));
    }

}

void StopNWaitSocket::Receive(string &message, int max_length) {

}
