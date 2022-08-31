#ifndef CLIENT_H
#define CLIENT_H

#include "NetworkHeaders.h"
#include <thread>
#include <future>
#include <mutex>
#include <random>

class Client {
        
    public :

        //constructor
        Client (int domain, int service, int protocol, int port, const char *ip_init);
        
        ~Client();

        //launch client
        void client_send_Msg();

        //getter
        int get_client_socket();

        std::atomic<bool> client_atomic;
        
        std::thread cli_thread;
    private :
      struct sockaddr_in srv; // struct to store information needed during programming
      int client_socket;
      void test_connection(int conn);
    
};
#endif
