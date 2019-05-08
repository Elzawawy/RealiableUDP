//
// Created by omar_swidan on 07/05/19.
//

#include "SocketHelper.h"

vector<SocketHelper::Packet> *SocketHelper::MakePackets(string &data, uint32_t seqno) {

    auto * packets=new vector<SocketHelper::Packet>;

    for (int i = 0; i < data.length(); ++i) {
        auto * packet_data=new string();

        if(i+this->max_packet_length<data.length())
            packet_data->append(
                    data.substr(
                            static_cast<unsigned long>(i),
                            static_cast<unsigned long>(i + this->max_packet_length-1)));

        else
            packet_data->append(
                    data.substr(
                            static_cast<unsigned long>(i),
                            i + data.length()-1));

        packets->push_back(Packet(0, static_cast<uint16_t>(packet_data->length()), seqno % UINT32_MAX, packet_data));
        i+=packet_data->length()-1;

    }

    return packets;
}

SocketHelper::SocketHelper(const uint16_t max_packet_length) : max_packet_length(max_packet_length) {}

SocketHelper::Packet::Packet(uint16_t cksum,  uint16_t len, uint32_t seqno, string *data) : cksum(
        cksum), len(len), seqno(seqno), data(data) {}
