//
// Created by zawawy on 5/10/19.
//
#include <string.h>
using namespace std;

#ifndef REALIABLEUDP_TESTINGSERVER_H
#define REALIABLEUDP_TESTINGSERVER_H

class TestingServer {
public:
    void startMyRUDPSocket(void);
    void startMyUDPSocket(void);
    int start(void);
    // get sockaddr, IPv4 or IPv6:
    void *get_in_addr(struct sockaddr *sa);
};


#endif //REALIABLEUDP_TESTINGSERVER_H
