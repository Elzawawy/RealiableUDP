cmake_minimum_required(VERSION 3.7.1)
project(RealiableUDP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_REQUIRED_FLAGS -D_POSIX_C_SOURCE=200112L)
set(CMAKE_CXX_FLAGS -pthread)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
add_executable(RealiableUDP main.cpp
        Socket.h UDPSocket.h UDPSocket.cpp
        RUDPSocket.h RUDPSocket.cpp SocketHelper.cpp SocketHelper.h
        Timer.cpp Timer.h
        StopNWaitSocket.cpp StopNWaitSocket.h GBNServer.cpp GBNClient.cpp
        TestingServer.h TestingClient.h TestingServer.cpp TestingClient.cpp
        )