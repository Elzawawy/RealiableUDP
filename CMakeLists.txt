cmake_minimum_required(VERSION 3.7.1)
project(RealiableUDP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_REQUIRED_FLAGS -D_POSIX_C_SOURCE=200112L)
set(CMAKE_CXX_FLAGS -pthread)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
add_executable(RealiableUDP src/main.cpp
        src/abstract_sockets/Socket.h src/unreliable_sockets/UDPSocket.h src/unreliable_sockets/UDPSocket.cpp
        src/reliable_sockets/go_back_N_socket/RUDPSocket.h src/reliable_sockets/go_back_N_socket/RUDPSocket.cpp src/utils/SocketHelper.cpp src/utils/SocketHelper.h
        src/utils/Timer.cpp src/utils/Timer.h
        src/reliable_sockets/stop_and_wait_socket/StopNWaitSocket.cpp src/reliable_sockets/stop_and_wait_socket/StopNWaitSocket.h src/servers/GBNServer.cpp src/clients/GBNClient.cpp
        src/servers/TestingServer.h src/clients/TestingClient.h src/servers/TestingServer.cpp src/clients/TestingClient.cpp
        )