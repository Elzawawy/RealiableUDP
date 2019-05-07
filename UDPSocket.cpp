//
// Created by zawawy on 5/1/19.
//

#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "UDPSocket.h"

UDPSocket::UDPSocket(UDPSocket::ip_version version, string ip_addr, string port_num) {

    struct addrinfo hints,*temp;
    int status=0;
    //make sure struct hints is empty
    memset(&hints, 0, sizeof hints);

    //set your needed parameters of Server.
    hints.ai_family = version;            //as input
    hints.ai_socktype = SOCK_DGRAM;      //UDP
    if (ip_addr.empty())
        hints.ai_flags = AI_PASSIVE;          //fill in my ip for me

    //Does all kinds of good stuff for us, including DNS and service name lookups, and fills out the structs we need.
    //Params: nullptr is for IP address for local host, 80 is port number ,hints is our required params.
    //results points to a linked list of struct addrinfo.
    if ((status = getaddrinfo((ip_addr.empty()? nullptr:ip_addr.c_str()), port_num.c_str(), &hints, &this->results_)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }

    // loop through all the results and bind to the first we can
    for (temp = results_; temp != nullptr; temp = temp->ai_next) {
        if ((sock_fd_ = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol)) == -1) {
            perror("socket");
            continue;
        }
        if(ip_addr.empty())
            if (bind(sock_fd_, temp->ai_addr, temp->ai_addrlen) == -1) {
             close(sock_fd_);
             perror("bind");
             continue;
            }
        break;
    }

    // looped off the end of the list with no successful bind
    if (temp == nullptr) {
        fprintf(stderr, "failed to bind socket\n");
        exit(2);
    }
    this->addr_=results_->ai_addr;
    this->addr_len_=results_->ai_addrlen;
    freeaddrinfo(results_); // all done with this structure

}

void UDPSocket::Receive(string &message, int max_length) {
    int rv;
    ssize_t numbytes;
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(this->sock_fd_, &message[0],(size_t)(max_length) , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

}

ssize_t UDPSocket::Send(string& message) {
    ssize_t num_bytes;
    if ((num_bytes = sendto(this->sock_fd_, message.c_str(), (size_t)(message.length()), 0,this->addr_,this->addr_len_)) == -1)
        perror("send");
    return num_bytes;
}
