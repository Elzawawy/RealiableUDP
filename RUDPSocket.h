//
// Created by zawawy on 5/7/19.
//

#ifndef RUDPSOCKET_H
#define RUDPSOCKET_H

#include <string>
#include <mutex>
#include <condition_variable>
#include "Socket.h"

using namespace std;

class RUDPSocket : Socket {
public:
    RUDPSocket(int send_maxsize);
    void Send(string& message) override;
    void Receive(string &message, int max_length) override;

private:
    typedef struct packet {
        /*Header*/
        unsigned short checksum;  // 16 bits
        unsigned short length;    // 16 bits
        unsigned int seqno;      // 32 bits
        /*Data*/
        char data[500];

    }Packet;
    void* sendpkt_th(Packet &packet, int th_id);
    int base_;
    int next_seq_num_;
    int sendwind_size_;
    mutex mtx_;                 // mutex for critical section
    condition_variable run_cv_;  // condition variable for critical section
    condition_variable recv_run_;
    bool ready_run_ = false;
    int current_thid_ = 0;
};


#endif //REALIABLEUDP_RUDPSOCKET_H
