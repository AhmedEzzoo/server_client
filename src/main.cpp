#include <NetworkHeaders.h>
#include "Server.h"
#include "Client.h"


int main (){
     
 Server serv =  Server(AF_INET, SOCK_STREAM, IPPROTO_TCP, 80, INADDR_ANY);
    
 serv.serv_thread = std::thread(&Server::server_launch, std::ref(serv)); 
    
 Client client = Client(AF_INET, SOCK_STREAM, IPPROTO_TCP, 80, "127.0.0.1");
      
 client.cli_thread = std::thread(&Client::client_send_Msg, std::ref(client));

  
  getchar();

 serv.server_atomic = true;
  
  return 0;
  
  
}