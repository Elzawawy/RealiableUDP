//
// Created by zawawy on 5/10/19.
//

#include "TestingClient.h"
#include "UDPSocket.h"
#include "StopNWaitSocket.h"
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

int TestingClient::start(int argc, char **argv) {
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    if (argc != 3) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
// loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }
    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0,
                           p->ai_addr, p->ai_addrlen)) == -1) {
        perror("talker: sendto");
        exit(1);
    }
    freeaddrinfo(servinfo);
    printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
    close(sockfd);
    return 0;
}

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
