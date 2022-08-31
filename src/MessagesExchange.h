#ifndef MESSAGESEXCHANGE_H
#define MESSAGESEXCHANGE_H

#include "NetworkHeaders.h"
#include <thread>
#include <mutex>
#include "Server.h"
#include "SocketConnection.h"

class Server;
class SocketConnection;
class MessagesExchange {

    public :

        MessagesExchange();

        ~MessagesExchange();

        void simulate(std::unique_ptr<SocketConnection> s_conn, Server *server);

        //function to read the msg from client 
        void recv_data (int y, Server *server);

    private :

     std::thread clients_thread;
    
    //mutex for thread guard
      std::mutex _mutex;

      
};



#endif