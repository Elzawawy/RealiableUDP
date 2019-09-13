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
        AckPacket(uint16_t cksum, uint16_t len, uint32_t ackno);
    };
    vector<Packet>*MakePackets(string &data, int protocol);
    string* PacketToString(Packet &pkt);
    Packet* StringToPacket(string &str);
    string* AckPacketToString(AckPacket &pkt);
    AckPacket* StringToAckPacket(string &str);
    bool IsCorrupt(Packet &pkt);
    vector<int>* GetBinaryVectorWithProbability(double probability_of_zeros,int length);

private:
    std::vector<std::string>* split_string(const std::string& str, const std::string& delimiter);
    std::vector<std::string> *split(std::string const & s, size_t count);
};


#endif //REALIABLEUDP_SOCKETHELPER_H
