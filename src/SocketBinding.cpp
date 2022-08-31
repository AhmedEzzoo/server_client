#include "SocketBinding.h"


SocketBinding::SocketBinding(int domain, int service, int protocol, int port,u_long ip_init)
: Socket(domain, service, protocol, port, ip_init ){
          
    //binding the socket 
    set_conn(network_connect(get_socket(), get_srv_addr()));

    // test binding success
    test_connection (get_conn());

    std::cout << "Server Binding" << std::endl; 

    }



//overwrite virtual network_connect
int SocketBinding::network_connect(int socket, struct sockaddr_in addr){
    return bind(socket, (struct sockaddr *)&addr, sizeof(addr));
}