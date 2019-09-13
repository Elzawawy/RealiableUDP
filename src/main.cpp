#include <iostream>
#include "servers/GBNServer.cpp"
#include "clients/GBNClient.cpp"
#include "clients/TestingClient.h"
#include "servers/TestingServer.h"
int main() {
    GBNServer s;
    GBNClient c;
    c.Start();
    return 0;
}