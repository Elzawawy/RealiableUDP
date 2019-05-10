//
// Created by zawawy on 5/10/19.
//
#include "UDPSocket.h"
#include "TestingServer.h"
#include "StopNWaitSocket.h"
#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <netdb.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>

#define MYPORT "4950"
// the port users will be connecting to
#define MAXBUFLEN 100

void TestingServer::startMyUDPSocket() {

    string buf;
    UDPSocket udpSocket = UDPSocket(UDPSocket::ipv4,"",MYPORT);
    udpSocket.Receive(buf,50);
    printf("listener: packet contains \"%s\"\n", &buf[0]);
}

void TestingServer::startMyRUDPSocket(void) {

    string buf;
    struct sockaddr_storage storage;
    //std::this_thread::sleep_for(std::chrono::milliseconds(20));
    StopNWaitSocket socket = StopNWaitSocket(UDPSocket::ipv4,"",MYPORT);
    cout<<"Created Socket."<<endl;
    socket.Receive(buf,50,storage);
    cout<<"Received filename, preparing for sending..."<<endl;
    std::ifstream t(&buf[0]);
    std::stringstream buffer;
    buffer << t.rdbuf();
    string string1 = buffer.str();
    //string string1 = "hoba lala";
    socket.Send(string1,storage);
    //std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //while(true);
    printf("listener: packet contains \"%s\"\n",&buf[0]);
}
