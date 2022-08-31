#include "MessagesExchange.h"


MessagesExchange::MessagesExchange(){
    
}

MessagesExchange::~MessagesExchange(){
  
    clients_thread.join();
    std::cout << "Messgaes Destructor" << std::endl;
}

 void MessagesExchange::recv_data (int y, Server *server){

      std::lock_guard<std::mutex> lock(_mutex);
     
       while (true){
         
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
      
        //buffer for receiving messages
         char buff[1024] = { 0, };    
    
          //return value of recv data
         int n_ret = recv(y, buff, 1024, 0);

        std::cout << "This is data from client ("<< y <<") will be dispalyed" << std::endl;
        
         //return value = 0 || 8  means that the client has been terminated
         if(n_ret <= KTcpCloseReq || n_ret == KHttpCloseReq) {

             //client has been closed or lost the connection
              server->client_closed_or_problem(y);
              break;
             }

         //means it is http request asking for main page
         else if (std::strncmp(buff, (KGetRequest).c_str(), 6) == 0)  {

              //data for connection request and ask for main page  
              server->http_data_get_request(buff, y);
              break; 
             }
         

         //means http socket request to connect
         else if (std::strncmp(buff, (KGetEndPoint).c_str(), 9) == 0){

             //data for connection request from websocket
              server->http_ws_conn_request(buff, y);
         }
         

        //data to request favicon.ico, So do nothing
         else if(std::strncmp(buff, (KGetFavicon).c_str(), 6) == 0) {

            //close the socket
            server->client_closed_or_problem(y);

            break ;
             }

        else  {

            if (server->server_atomic)  break;

            server->read_tcp_data (buff);
        }
      
    }
        server->_test.erase(std::find(server->_test.begin(), server->_test.end(), std::this_thread::get_id())); 
 }

void MessagesExchange::simulate(std::unique_ptr<SocketConnection> s_conn, Server *server){

      std::lock_guard<std::mutex> _lock(_mutex);

     clients_thread = std::thread(&MessagesExchange::recv_data, this, s_conn->get_client_socket(), server);
     server->_test.push_back(clients_thread.get_id());

     std::cout << server->_test.size() << std::endl;
}
