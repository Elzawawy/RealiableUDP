//
// Created by omar_swidan on 09/05/19.
//

#include "../reliable_sockets/go_back_N_socket/RUDPSocket.h"

class GBNClient{
public:
    void Start(){
        RUDPSocket socket_(50,Socket::ipv4,"localhost","3000");
        string message="Iago Aspas"
                       " Juncal is a Spanish professional"
                       " footballer who plays as a striker for"
                       " RC Celta de Vigo and the Spain national team."
                       " He has spent most of his career with Celta, appearing"
                       " in more than 300 official games over nine seasons"
                       " and scoring more than 130 goals. Wikipedia";
        sockaddr_storage storage;
        socket_.Send(message);
        socket_.Receive(message,1001);

    }
};
