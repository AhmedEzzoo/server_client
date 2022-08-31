#ifndef BINDINGSOCKET_H
#define BINDINGSOCKET_H

#include "NetworkHeaders.h"
#include "Socket.h"

//inherit from parent Socket
class SocketBinding : public Socket{

    public :
     SocketBinding(int domain, int service, int protocol, int port, u_long ip_init);

      //overwrite the virtual function network_connect
     int network_connect(int socket, struct sockaddr_in addr);

};

#endif