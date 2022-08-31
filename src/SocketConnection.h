#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H
#include "NetworkHeaders.h"
#include <thread>
#include "Server.h"


using namespace WebSocket; 


class SocketConnection {

    public :
         SocketConnection ();
    
         ~SocketConnection();

         SocketStatus accept_connection(int serv_socket, struct sockaddr_in addr, int *addr_len);
         
         int get_client_socket();

    private :

        int client_socket;       

};

#endif