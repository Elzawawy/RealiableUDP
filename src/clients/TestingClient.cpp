//
// Created by zawawy on 5/10/19.
//

#include "TestingClient.h"
#include "../unreliable_sockets/UDPSocket.h"
#include "../reliable_sockets/stop_and_wait_socket/StopNWaitSocket.h"
/*
** talker.c -- a datagram "client" demo
*/
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <fstream>
#include <iostream>

#define SERVERPORT "4950"
// the port users will be connecting to


void TestingClient::startMyUDPSocket(char *argv[]) {
    UDPSocket udpSocket = UDPSocket(UDPSocket::ipv4,argv[1],SERVERPORT);
    udpSocket.Send(reinterpret_cast<string &>(argv[2]));
    printf("talker: sent bytes to %s\n", argv[1]);
}

void TestingClient::startMyRUDPSocket(char **argv) {
    StopNWaitSocket socket = StopNWaitSocket(UDPSocket::ipv4,argv[1],SERVERPORT);
    cout<<"Created socket..."<<endl;
    string s(argv[2]);
    string news;
    cout<<"Requesting file from server..."<<endl;
    socket.Send(s);
    cout<<"Waiting to receive of file..."<<endl;
    socket.Receive(news,40000000);
    printf("talker: sent bytes to %s\n", argv[1]);
    std::ofstream file("file2.txt");
    file << news;

}
