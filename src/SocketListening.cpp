#include "SocketListening.h"

//constructor
SocketListening::SocketListening
(int domain, int service, int protocol, int port, u_long ip_init)
:SocketBinding(domain, service, protocol, port, ip_init)
{
    //start listen and set listening value
    listen_socket();
     /*set_conn(network_connect(get_socket(), get_srv_addr()));*/

    //test the listen_result
    test_connection(listen_result);
    std::cout << "Server Listening" << std::endl;
}

/*overwrite the virtual network_connect
 int SocketListening::network_connect(int socket, struct sockaddr_in addr){
     return listen(get_socket(), 5);
 }*/

 void SocketListening::listen_socket(){

     //calling listen function with maximum 5 clients
     listen_result = listen(get_socket(), 5);
 }
