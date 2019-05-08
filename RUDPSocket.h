//
// Created by zawawy on 5/7/19.
//

#ifndef REALIABLEUDP_RUDPSOCKET_H
#define REALIABLEUDP_RUDPSOCKET_H
#include "Socket.h"

class RUDPSocket : Socket {
public:
    RUDPSocket(int send_maxsize);
    void Send() override;
    void Receive() override;

private:
    int base_;
    int next_seq_num_;
    int sendwind_size_;

    void SIGUSR1_handler(int sig);
};


#endif //REALIABLEUDP_RUDPSOCKET_H
