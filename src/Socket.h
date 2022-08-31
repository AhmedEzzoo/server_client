#ifndef SOCKET_H
#define SOCKET_H

#include "NetworkHeaders.h"



class Socket {

    private :
    struct sockaddr_in srv_addr; // struct to store information needed during programming
    int s_socket;
    int connection;
    
    public :
        Socket (int domain, int service ,int protocol, int port, u_long ip_inti);
        void test_connection (int conn);
        virtual int network_connect (int socket, struct sockaddr_in addr) = 0;
        //getter
        int get_socket();
        int get_conn();
        struct sockaddr_in get_srv_addr ();
        void set_conn(int conn);
       


};



#endif