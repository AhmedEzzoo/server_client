cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

project(ServerTest)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")



include_directories(src)

find_package(OpenSSL REQUIRED)
add_executable(Server src/main.cpp src/SocketBinding.cpp src/Socket.cpp src/SocketConnection.cpp src/SocketListening.cpp src/Server.cpp src/HttpMainPage.cpp src/Client.cpp src/MessagesExchange.cpp)
target_link_libraries(Server OpenSSL::SSL)
if(WIN32)
  target_link_libraries(Server wsock32 ws2_32)
endif()