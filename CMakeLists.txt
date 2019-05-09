cmake_minimum_required(VERSION 3.10.2)
project(RealiableUDP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_REQUIRED_FLAGS -D_POSIX_C_SOURCE=200112L)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(RealiableUDP main.cpp
        Socket.h UDPSocket.h UDPSocket.cpp
        RUDPSocket.h RUDPSocket.cpp SocketHelper.cpp SocketHelper.h
        Timer.cpp Timer.h
        StopNWaitSocket.cpp StopNWaitSocket.h Server.cpp Client.cpp)