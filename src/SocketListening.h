#ifndef SOCKETLISTENING_H
#define SOCKETLISTENING_H

#include "NetworkHeaders.h"
#include "SocketBinding.h"

//inherit from Parent Socket class
class SocketListening : public SocketBinding {

    public :
    //constructor
      SocketListening(int domain, int service, int protocol, int port, u_long ip_Init);

   //test listening function
    void listen_socket ();
    //int network_connect (int socket, struct sockaddr_in addr);

    private :
      int listen_result;
};



#endif