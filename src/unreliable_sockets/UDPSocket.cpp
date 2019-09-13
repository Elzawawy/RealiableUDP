//
// Created by zawawy on 5/1/19.
//

#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include "UDPSocket.h"
#include <iostream>

/**
 *
 * @param version the ip version ipv4, ipv6 or undefined to use any
 * @param ip_addr the ip address to be udsed either as a sending or receiving socket
 * @param port_num the port number to be used
 */
UDPSocket::UDPSocket(UDPSocket::ip_version version, string ip_addr, string port_num) {

    struct addrinfo hints,*temp;
    int status=0;
    //make sure struct hints is empty
    memset(&hints, 0, sizeof hints);

    //set your needed parameters of GBNServer.
    hints.ai_family = version;            //as input
    hints.ai_socktype = SOCK_DGRAM;      //UDP
    if (ip_addr.empty())
        hints.ai_flags = AI_PASSIVE;          //fill in my ip for me

    //Does all kinds of good stuff for us, including DNS and service name lookups, and fills out the structs we need.
    //Params: nullptr is for IP address for local host, 80 is port number ,hints is our required params.
    //results points to a linked list of struct addrinfo.
    if ((status = getaddrinfo((ip_addr.empty()? nullptr:ip_addr.c_str()), port_num.empty()?"3000":port_num.c_str(), &hints, &this->results_)) != 0) {
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
//             close(sock_fd_);
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
    char buffer[max_length];
    if ((numbytes = recvfrom(this->sock_fd_, buffer,(size_t)(max_length) , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    message = string(buffer, static_cast<unsigned long>(numbytes));
    std::cout<<"Recieved"<<numbytes<<"+++"<<message<<endl;
}

void UDPSocket::Send(string& message) {
    ssize_t num_bytes;
    if ((num_bytes = sendto(this->sock_fd_, message.c_str(), (size_t)(message.length()), 0,this->addr_,this->addr_len_)) == -1)
        perror("send");
    cout<<"bytes sent"<<num_bytes<<endl;
    cout<<"bytes sent should be of size "<<message.length()<<endl;

}

int UDPSocket::ReceiveTillTimeout(string &message, int max_length, int timeout) {
    string buffer;
    fd_set readfds;
    struct timeval tv;
    string request;
    buffer.clear();
    buffer.resize(max_length);
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;
    int bytes_read = 0;
    // clear the set ahead of time
    FD_ZERO(&readfds);
    // add our descriptors to the set
    FD_SET(sock_fd_, &readfds);
    // wait until either socket has data ready to be recv()d
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    //cout<<"Ana mstny y3m"<<endl;
    int rv = select(sock_fd_ + 1, &readfds, nullptr, nullptr, &tv);
    //cout<<rv<<"Ana gali haga y3m"<<endl;
    if (rv == -1) {
        perror("select");
        bytes_read = 0;
    } else if (rv == 0) bytes_read = 0;
    else {
        if (FD_ISSET(sock_fd_, &readfds)) {
            bytes_read = static_cast<int>(recvfrom(sock_fd_, &buffer[0], (size_t) max_length, 0,
                                                   (struct sockaddr *) &their_addr, &addr_len));
        }
    }
    if(bytes_read != 0)
    {
        message.clear();
        buffer[bytes_read] ='\0';
        message = &buffer[0];
    }
    return bytes_read;


}

void UDPSocket::Send(string &message, struct sockaddr_storage storage) {
    ssize_t num_bytes;
    socklen_t addr_len = sizeof (struct sockaddr_storage);
    if ((num_bytes = sendto(this->sock_fd_, message.c_str(), (size_t) (message.length()), 0, (struct sockaddr *)&storage,addr_len)) == -1)
        perror("send");
    cout<<"bytes sent"<<num_bytes<<endl;
    cout<<"bytes sent should be of size "<<message.length()<<endl;

}

int UDPSocket::ReceiveTillTimeout(string &message, int max_length, int timeout, struct sockaddr_storage &storage) {
    string buffer;
    fd_set readfds;
    struct timeval tv;
    buffer.clear();
    buffer.resize(max_length);
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;
    int bytes_read;
    // clear the set ahead of time
    FD_ZERO(&readfds);
    // add our descriptors to the set
    FD_SET(sock_fd_, &readfds);
    // wait until either socket has data ready to be recv()d
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    int rv = select(sock_fd_ + 1, &readfds, nullptr, nullptr, &tv);
    if (rv == -1) {
        perror("select");
        bytes_read = 0;
    } else if (rv == 0) bytes_read = 0;
    else {
        if (FD_ISSET(sock_fd_, &readfds)) {
            bytes_read = static_cast<int>(recvfrom(sock_fd_, &buffer[0], (size_t) max_length, 0,
                                                   (struct sockaddr *) &their_addr, &addr_len));
        }
    }
    if(bytes_read != 0)
    {
        message.clear();
        buffer[bytes_read] ='\0';
        message = &buffer[0];
        storage = their_addr;
    }
    return bytes_read;
}

void UDPSocket::Receive(string &message, int max_length, struct sockaddr_storage &storage) {
    ssize_t numbytes;
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof their_addr;
    char buffer[max_length];
    if ((numbytes = recvfrom(this->sock_fd_, buffer,(size_t)(max_length) , 0,(sockaddr*)&their_addr, &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }
    message = string(buffer, static_cast<unsigned long>(numbytes));
    storage = their_addr;

    std::cout<<"Recieved"<<numbytes<<" "<<message<<endl;

}



