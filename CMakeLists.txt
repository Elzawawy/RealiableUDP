cmake_minimum_required(VERSION 3.10.2)
project(RealiableUDP)

set(CMAKE_CXX_STANDARD 17)

add_executable(RealiableUDP main.cpp
        Socket.h UDPSocket.h UDPSocket.cpp
        RUDPSocket.h RUDPSocket.cpp SocketHelper.cpp SocketHelper.h Timer.cpp Timer.h)