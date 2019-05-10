#include <iostream>
#include "Server.cpp"
#include "Client.cpp"
#include "TestingClient.h"
#include "TestingServer.h"
int main() {
//    TestingServer s;
//    s.startMyRUDPSocket();
//
//    TestingClient c;
//    c.startMyRUDPSocket();
    SocketHelper socketHelper(500);
    socketHelper.GetBinaryVectorWithProbability(0.75,10);
    return 0;
}