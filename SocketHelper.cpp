//
// Created by omar_swidan on 07/05/19.
//

#include <sstream>
#include <iostream>
#include <random>
#include "SocketHelper.h"

//Modular sum
uint16_t checksum(const char* s)
{
    uint16_t sum = 0;
    while (*s != 0)
    {
        sum += *s-'0';
        s++;
    }
    return sum;
}
vector<SocketHelper::Packet> *SocketHelper::MakePackets(string &data,int protocol) {
    auto * packets=new vector<SocketHelper::Packet>;
    int seqno = -1;
    int alternate = 0;
    vector<std::string> *strings = split(data,max_packet_length);
    for (auto &string : *strings) {
        if(protocol == 0)
            packets->push_back(Packet(checksum(string.c_str()), static_cast<uint16_t>(string.size()), (seqno + 1) % UINT32_MAX, &string));
        else
            packets->push_back(Packet(checksum(string.c_str()), static_cast<uint16_t>(string.size()), static_cast<uint32_t>(alternate), &string));
        alternate = !alternate;
    }
    return packets;
}

SocketHelper::SocketHelper(const uint16_t max_packet_length) : max_packet_length(max_packet_length) {}

string *SocketHelper::PacketToString(SocketHelper::Packet &pkt) {
    auto * pkt_string = new string;
    pkt_string->append(std::to_string(pkt.cksum)+"\n");
    pkt_string->append(std::to_string(pkt.len)+"\n");
    pkt_string->append(std::to_string(pkt.seqno)+"\n");
    pkt_string->append(*pkt.data);
    return pkt_string;
}

SocketHelper::Packet *SocketHelper::StringToPacket(string &str) {
    std::vector<std::string> *strings = split_string(str, "\n");
    auto * data = new string;
    for(int i=3;i<strings->size();i++){
        if(i+1 < strings->size())
            data->append((*strings)[i]+"\n");
        else
            data->append((*strings)[i]);
    }
    return new Packet(static_cast<uint16_t>(stoi((*strings)[0])),
                      static_cast<uint16_t>(stoi((*strings)[1])),
                      static_cast<uint32_t>(stoi((*strings)[2])),
                      data);
}

std::vector<std::string> *SocketHelper::split_string(const std::string &str, const std::string &delimiter) {
    auto *strings =  new std::vector<std::string>;
    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings->push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings->push_back(str.substr(prev));

    return strings;
}

string *SocketHelper::AckPacketToString(SocketHelper::AckPacket &pkt) {
    auto * pkt_string = new string;
    pkt_string->append(std::to_string(pkt.cksum)+"\n");
    pkt_string->append(std::to_string(pkt.len)+"\n");
    pkt_string->append(std::to_string(pkt.ackno)+"\n");
    return pkt_string;
}

SocketHelper::AckPacket *SocketHelper::StringToAckPacket(string &str) {
    std::vector<std::string> *strings = split_string(str, "\n");
    return new AckPacket(static_cast<uint16_t>(stoi((*strings)[0])),
                         static_cast<uint16_t>(stoi((*strings)[1])),
                         static_cast<uint32_t>(stoi((*strings)[2])));

}

std::vector<std::string>* SocketHelper::split(std::string const &s, size_t count) {
    auto *strings = new vector<std::string>;
    for (unsigned i = 0; i < s.length(); i += count) {
        strings->push_back(s.substr(i, count));
    }
    return strings;
}

bool SocketHelper::IsCorrupt(SocketHelper::Packet &pkt) {
    return pkt.cksum != checksum(pkt.data->c_str());
}

SocketHelper::Packet::Packet(uint16_t cksum,  uint16_t len, uint32_t seqno, string *data) : cksum(
        cksum), len(len), seqno(seqno), data(data) {}

SocketHelper::AckPacket::AckPacket(uint16_t cksum, uint16_t len, uint32_t ackno) : cksum(cksum),len(len), ackno(ackno){}

vector<int> *SocketHelper::GetBinaryVectorWithProbability(const double probability_of_zeros,const int length) {
    auto * binary_vector=new vector<int>;
    auto initializer_list={probability_of_zeros,1-probability_of_zeros};
    std::random_device r;
    std::default_random_engine e1(r());
    // Distribution that defines different weights for numbers.
    std::discrete_distribution<int> discrete_dist(initializer_list);
    for (int i = 0; i < length; ++i) {
        binary_vector->push_back(static_cast<int &&>(std::round(discrete_dist(e1))));
    }
    return binary_vector;
}