//
// Created by zawawy on 5/7/19.
//

#ifndef RUDPSOCKET_H
#define RUDPSOCKET_H

#include <string>
#include "Socket.h"

using namespace std;

class RUDPSocket : Socket {
public:
    RUDPSocket(int send_maxsize);
    void Send(string& message) override;
    void Receive(string &message, int max_length) override;

private:
    int base_;
    int next_seq_num_;
    int sendwind_size_;
};


#endif //REALIABLEUDP_RUDPSOCKET_H
