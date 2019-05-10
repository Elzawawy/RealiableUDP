#include <iostream>
#include "GBNServer.cpp"
#include "GBNClient.cpp"
#include "TestingClient.h"
#include "TestingServer.h"
int main() {
    GBNServer s;
    GBNClient c;
    c.Start();
    return 0;
}