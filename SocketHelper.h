//
// Created by omar_swidan on 07/05/19.
//

#ifndef REALIABLEUDP_SOCKETHELPER_H
#define REALIABLEUDP_SOCKETHELPER_H


#include <cstdint>
#include <vector>
#include <string>
#include <stdint.h>
using namespace std;
class SocketHelper {
public:
    const uint16_t max_packet_length;

    explicit SocketHelper(uint16_t max_packet_length);

    struct Packet{

    const uint16_t cksum;
    const uint16_t len;
    const uint32_t seqno;

    string* data;

        Packet(uint16_t cksum, uint16_t len, uint32_t seqno, string *data);
    };
    struct AckPacket{
        uint16_t cksum;
        uint16_t len;
        uint32_t ackno;

        string* data;
    };
    vector<Packet>*MakePackets(string &data, uint32_t seqno);
};


#endif //REALIABLEUDP_SOCKETHELPER_H
