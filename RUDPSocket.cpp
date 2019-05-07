//
// Created by zawawy on 5/7/19.
//

#include "RUDPSocket.h"

void RUDPSocket::Send() {

}

void RUDPSocket::Receive() {

}

RUDPSocket::RUDPSocket(int send_maxsize) {

    // Initialize variables used in GBN.
    this->base_ = 1;
    this->next_seq_num_ = 1;
    // Initialize Sending sliding window maximum size.
    this->sendwind_size_ = send_maxsize;
}
