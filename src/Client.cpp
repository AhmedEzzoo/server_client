#include <Client.h>


 Client::Client (int domain, int service, int protocol, int port, const char *ip_init)
 {
     //used WSA is for windows operating system only
        WSADATA ws;
    if (WSAStartup(MAKEWORD(2,2), &ws) < 0){
          std::cout << "WSA failed initialize\n";
    }
    
    //address implementation
    srv.sin_family = domain;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = inet_addr(ip_init);
    memset(&srv.sin_zero, 0, 8);

     //connect to socket or open socket
    client_socket = socket(domain, service, protocol);

    //test connection or opened socket success
    test_connection (client_socket);

    //connect to Server
    int conn_ret = connect(client_socket, (struct sockaddr *) &srv, sizeof(srv));

    test_connection (conn_ret);
   
    client_atomic = false;
 }

  Client::~Client (){

      //terminate thread loop
      client_atomic = true;

      //wait finish the whole thread
      cli_thread.join();
      
      std::cout << "Client Destructor Called !!!!!!!!!!" << std::endl;
  }

 void Client::test_connection (int conn){
    if (conn < 0){
        WSACleanup(); // only for windows
        perror("Connection Faild!!!!");
        exit(EXIT_FAILURE);
    }
}

void Client::client_send_Msg(){

  	std::this_thread::sleep_for(std::chrono::seconds(2));
    //generate random numbers for simulation      
    std::random_device rand_dev;
    std::mt19937 mt(rand_dev());
    std::uniform_int_distribution<int> rNum_1(0, 80);
    std::uniform_int_distribution<int> rNum_2(0, 120);
    std::uniform_int_distribution<int> rNum_3(0, 160);
    auto dur_1 = std::chrono::duration<int> (rNum_1(mt));
    auto dur_2 = std::chrono::duration<int> (rNum_2(mt));
    auto dur_3 = std::chrono::duration<int> (rNum_3(mt));

    while (true){

         if(client_atomic) break;

        //update the number every 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));

        //put the number in buffer to send random number_1
        std::string buffer_send_msg = "S1=" + std::to_string(dur_1.count());

        //generate new random number_2
        buffer_send_msg.append(" S2=" + std::to_string(dur_2.count()));

        //generate new random number_3
        buffer_send_msg.append(" S3=" + std::to_string(dur_3.count()));

        //send the reading to server 
        send(client_socket, buffer_send_msg.c_str(), strlen(buffer_send_msg.c_str()), 0);

        //update or generate new random number
        dur_1 = std::chrono::duration<int> (rNum_1(mt));
        dur_2 = std::chrono::duration<int> (rNum_2(mt));
        dur_3 = std::chrono::duration<int> (rNum_3(mt));
      
      
    }
}

int Client::get_client_socket(){ return client_socket ;}
