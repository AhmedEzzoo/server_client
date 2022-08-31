#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <future>
#include <mutex>
#include "NetworkHeaders.h"
#include "SocketListening.h"
#include "HttpMainPage.h"
#include "SocketConnection.h"
#include "MessagesExchange.h" 


using namespace WebSocket;
class Server {

    public :
        //Constructor
       Server(int domain, int service, int protocol, int port,  u_long ip_init);

       ~Server(); 
       //infinit loop for connections and recv msg 
       void server_launch();
       
       //Server connect to socket and read the header
       void server_connection_handle ();

       //request for main page and send it
       int send_main_page(int &sock, char* data, int data_len);

       //server starts listening to the socket and address
       void get_socket_addr ();

       //to send data to browser via ws
       void send_to_http_socket_data(std::string const buff_to_send,int &cli_sock);

       //client end the session or has problem
       void client_closed_or_problem(int &cli_sock);

       //read the data from http_socket
       void read_http_socket_data (char *buff, int &cli_socket);
       
       //read ws from browser conn request
       void http_ws_conn_request(char *buff, int &cli_sock);

       //get request from browser
       void http_data_get_request(char *buff, int &cli_sock);

       //read normal tcp client data 
       void read_tcp_data (char *buff);

        //flage to terminate thread loop
       std::atomic<bool> server_atomic;
     
       
       std::thread serv_thread ; 

       std::vector <std::thread::id> _test;

    private:
       
       //Server has a socket to listen to 
       std::unique_ptr<SocketListening> sock_listen;   //owend
       
       //Server has a main page 
       std::unique_ptr<HttpMainPage> serv_main_page;

        std::vector <int> http_ws_queue;

        //server socket
        int server_sock;

        struct sockaddr_in addr;

        //file reader only as we need
        fd_set fr;

        //max number of file description
        int max_fd;

        //struct for receiving data from browser socket
        struct recv_bytes {
             uint8_t first_byte ;
             uint8_t sec_byte ;
             uint8_t length;
             uint8_t index_of_first_mask;
             uint8_t index_of_first_data;
             uint8_t masks[4];

        };        
    
};


#endif