#include "Server.h"
#include <openssl/sha.h>

Server::Server(int domain, int service, int protocol, int port, u_long ip_init){
     
     //instantiation for the socket to listen to it
     sock_listen = std::make_unique<SocketListening>
     (domain, service, protocol, port, ip_init);

     //instantiate main page
     serv_main_page = std::make_unique<HttpMainPage>(); 
  
  	 server_atomic = false;
   
}

Server::~Server(){

      std::cout << "Server Destructor!!!!!" << std::endl;

      //make sure all threads has been terminated
      std::cout << _test.size() << std::endl;

      //terminate the server thread
      serv_thread.native_handle();
      
      //terminate the programe
      exit(0);    
}

int Server::send_main_page(int &sock, char* data, int data_len){
     
        int send_result ;
        const char* p_data = (const char *)data;
        while (data_len > 0){
            send_result = send(sock, p_data, data_len, 0);
            if (send_result < 0) return -1;
            p_data += send_result;
            data_len-=send_result;
        }
        return 0;
 }

 
void Server::get_socket_addr (){

     //Socket which server listening to 
     server_sock = sock_listen->get_socket();
     
     //address
     addr = sock_listen->get_srv_addr();

     max_fd = server_sock;

}

void Server::server_connection_handle (){
    
             //std::lock_guard<std::mutex> lock_g(_mutex);

      std::unique_ptr<SocketConnection> conn = std::make_unique <SocketConnection> ();
      std::shared_ptr<MessagesExchange> msg = std::make_shared<MessagesExchange>();
                
       //length of the address
       int addr_len = sizeof(sockaddr);       
   
       //wait until get request to accept new connection
       if  (conn->accept_connection(server_sock , addr, &addr_len) == SocketStatus::SocketOpen);
              { 
                 std::cout << "This is request to connect from ("<< conn->get_client_socket() <<")and is gonna be handled" << std::endl;
                
                 sleep(1);
                 msg->simulate(std::move(conn), this);
              }  
}

void Server::read_tcp_data (char *buff){

    std::cout << buff << std::endl;

    //send the message to all browsers
    if (http_ws_queue.size() > 0){
    for (auto &y: http_ws_queue) 
    send_to_http_socket_data(buff, y);
    }
}


void Server::http_ws_conn_request(char *buff, int &cli_sock){

         //add the socket to htttp_ws_client queue
         http_ws_queue.emplace_back(cli_sock);

         std::cout << "Message from client " << cli_sock << " : " << buff ;
                    
         //main page header prepare 
         std::string header_ws = serv_main_page->get_ws_header();
         std::string header_ws_cont = buff;
         std::string line;
         std::string value;
         std::string key;
         size_t flag = 0;
         std::istringstream ss(header_ws_cont);
         while (std::getline(ss, line)){
         std::istringstream line_stream(line);
         while (line_stream >> key >> value) {
             if (key == KWebsocketKey){
                flag = 1;
                break;
               } 
            }
             if (flag == 1) break;
        }

        //std::cout << value << std::endl;
              
        //add the magic key to it   
        value.append(KMagicString);

        //convert to security hex algorithm SHA
        char *sha_ret = (char *)SHA1(reinterpret_cast<const unsigned char*>(value.c_str()), value.length(), nullptr);
                   
        //std::cout << sha_ret << std::endl;
        std::string sha_s(sha_ret);
                    
        //encode the new ws key and add it to server accept key
        header_ws.append(serv_main_page->base64_encode(reinterpret_cast<const char*>(sha_ret), strlen(sha_ret)));
                    
        //add line terminate and carriage return
        header_ws.append("\r\n");
        header_ws.append("\r\n");
                    
        //std::cout << "ws Header to send : " << header_ws << std::endl;

        //send and check if the header is sent properly
        if (send_main_page(cli_sock, (char*)header_ws.c_str(), header_ws.length()) < 0)
        std::cout << "Sending header Failed\n";
}

void Server::http_data_get_request(char *buff, int &cli_sock){

            std::cout << "Message from client " << cli_sock << " : " << buff ;

            //main page header prepare 
            std::string header = serv_main_page->get_http_header();

            //http page prepare
            std::string page = serv_main_page->get_http_page();

            //check if the header is sent properly
            if (send_main_page(cli_sock, (char *)header.c_str(), header.size()) < 0)
            std::cout << "Sending header Failed\n";

            //check if the main page is sent properly
            if (send_main_page(cli_sock, (char *)page.c_str(), page.size()) < 0) 
            std::cout << "Sending data Failed \n";

            //close the http request socket
            closesocket(cli_sock);

}

void Server::read_http_socket_data (char *buff, int &cli_socket){
                  
            //struct foir manupilating incoming data
            recv_bytes bytes;

            //first byte of data put it in sec byte of struct
            bytes.sec_byte = buff[1];

            //the bytes length & with 127 to decoded the mask of encoded data
            bytes.length = bytes.sec_byte & WebsocketFrameSize::BigFrame;
                  
            //the value of the index of first mask which depend on message
            bytes.index_of_first_mask = WebsocketDataStream::SmallStream;

            // means that the next 2 bytes are for length
            if (bytes.length == WebsocketFrameSize::MeduimFrame)     
            bytes.index_of_first_mask = 4;

            //means that next 8 bytes for length
            else if (bytes.length == WebsocketFrameSize::BigFrame) 
            bytes.index_of_first_mask = 10;
                  
            //insert the incoming mask bytes of encoded msg in mask array
            bytes.masks[0] = buff[bytes.index_of_first_mask];
            bytes.masks[1] = buff[bytes.index_of_first_mask + 1];
            bytes.masks[2] = buff[bytes.index_of_first_mask + 2];
            bytes.masks[3] = buff[bytes.index_of_first_mask + 3];
                  
            //calculate the index of first data bytes
            bytes.index_of_first_data = bytes.index_of_first_mask + WebsocketDataStream::MeduimStream; 
                  
            //to calculate the length of the total bytes of whole message
            std::string msg (buff);
            int len = msg.length();

            //calculate the length of data bytes
            int msg_len = len - bytes.index_of_first_data;

            uint8_t  decoded_msg [msg_len];

            //insert the data only after decoding
            for (size_t i = bytes.index_of_first_data, j = 0; i < len ; i++, j++){
                       decoded_msg[j] = buff[i] ^ bytes.masks[j % WebsocketDataStream::MeduimStream];
                   } 
                   
            //display data
            std::cout << decoded_msg << std::endl;
           // send_to_http_socket_data(cli_socket);
}

void Server::send_to_http_socket_data(std::string const buff_to_send, int &cli_sock){

         //std::string const buff_to_send = "Hello Client How Are you";
         
         //length of data to be sent
         long long data_len = buff_to_send.length();
         
         //allocate buffer to fill for sending on heap
         char* bytes_to_send = new char [10 + data_len];
         
         //129 fixed first byte to send
         bytes_to_send[0] = 129;

          //index for data stream
         int index_start_Data = -1;


         //check the needed frame size to send
         if (buff_to_send.length() <= WebsocketFrameSize::SmallFrame){

              bytes_to_send[1] = data_len;
              index_start_Data = WebsocketDataStream::SmallStream;

         }else if (buff_to_send.length() >= WebsocketFrameSize::MeduimFrame && buff_to_send.length() <= 65535){
              
              /*
              second byte of frame contains the frame size
              third and fourth are the starting of data stream
              */
              bytes_to_send[1] =  WebsocketFrameSize::MeduimFrame;
              bytes_to_send[2] = (data_len >> 8) & 255;
              bytes_to_send[3] = (data_len & 255);
              index_start_Data =  WebsocketDataStream::MeduimStream;
         }else{

              /*
              second byte of frame contains the frame size
              next eight bytes are the starting of data stream
              */
              bytes_to_send[1] = WebsocketFrameSize::BigFrame;
              bytes_to_send[2] = (data_len >> 56) & 255;
              bytes_to_send[3] = (data_len >> 48) & 255;
              bytes_to_send[4] = (data_len >> 40) & 255;
              bytes_to_send[5] = (data_len >> 32) & 255;
              bytes_to_send[6] = (data_len >> 24) & 255;
              bytes_to_send[7] = (data_len >> 16) & 255;
              bytes_to_send[8] = (data_len >>  8) & 255;
              bytes_to_send[9] = (data_len & 255);
              index_start_Data =  WebsocketDataStream::BigStream;
             
         }  

        //put the data in char * stream to send
        std::copy(buff_to_send.begin(), buff_to_send.end(), &bytes_to_send[index_start_Data]);

        //send data as one shoot 
        send(cli_sock, bytes_to_send, (index_start_Data + data_len), 0);

        //delete the allocated heap for the bytes to send
        delete [] bytes_to_send;
}



void Server::client_closed_or_problem(int &cli_sock){

            std::cout << "Server : Something wrong Happened. close the connection to socket ("<< cli_sock <<")" << std::endl;
         
            //close the client socket from server side
            closesocket(cli_sock);
}

void Server::server_launch(){

    //get socket and addr
    get_socket_addr (); 
      
    //Infinit loop for connections and read the client msg
    while (true){

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
        std::cout << "Waiting for request" << std::endl;

        std::cout << "Press Enter Key to shutdown Server" << std::endl;

        //server waiting to accept connection or get the new messages
        server_connection_handle ();

        std::cout << "\n..........Done..........\n"; 
    }
}
