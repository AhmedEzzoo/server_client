#include "SocketConnection.h"

//constructor
SocketConnection::SocketConnection()
{
    
}

SocketConnection::~SocketConnection (){

    std::cout << "connection Destructor" << std::endl;
}

SocketStatus SocketConnection::accept_connection
 (int serv_socket, struct sockaddr_in addr, int *addr_len){
     
     client_socket = accept(serv_socket , (struct sockaddr *)&addr, (socklen_t *)&addr_len);
    return (client_socket > 0) ? SocketStatus::SocketOpen : SocketStatus::SocketClose;

 }
  int SocketConnection::get_client_socket(){
      return client_socket;
  }
 