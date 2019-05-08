//
// Created by omar_swidan on 07/05/19.
//

#include <sstream>
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

string *SocketHelper::pkt_tostring(SocketHelper::Packet &pkt) {
    auto * pkt_string = new string;
    pkt_string->append(std::to_string(pkt.cksum)+"\n");
    pkt_string->append(std::to_string(pkt.len)+"\n");
    pkt_string->append(std::to_string(pkt.seqno)+"\n");
    pkt_string->append(*pkt.data);
    return pkt_string;
}

SocketHelper::Packet *SocketHelper::string_topkt(string &str) {
    std::vector<std::string> strings = split_string(str, "\n");
    return new Packet(stoi(strings[0]),stoi(strings[1]),stoi(strings[2]),&strings[3]);
}

std::vector<std::string> SocketHelper::split_string(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> strings;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

SocketHelper::Packet::Packet(uint16_t cksum,  uint16_t len, uint32_t seqno, string *data) : cksum(
        cksum), len(len), seqno(seqno), data(data) {}
