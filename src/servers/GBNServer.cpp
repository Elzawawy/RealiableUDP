//
// Created by omar_swidan on 09/05/19.
//

#include <iostream>
#include "../reliable_sockets/go_back_N_socket/RUDPSocket.h"

class GBNServer{
public:
    void Start(){

        RUDPSocket socket_(50,Socket::ipv4,"","3000") ;
        string message="Hello my friends";
        string RecievedMessage;
        sockaddr_storage storage;
        socket_.Receive(RecievedMessage,501,storage);

        socket_.Send(message,storage);
    };
};
