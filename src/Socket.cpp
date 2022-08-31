#include <Socket.h>

Socket::Socket(int domain, int service, int protocol, int port, u_long ip_init){

   //used WSA is for windows operating system only
        WSADATA ws;
    if (WSAStartup(MAKEWORD(2,2), &ws) < 0){
          std::cout << "WSA failed initialize\n";
    }
    
    //address implementation
    srv_addr.sin_family = domain;
    srv_addr.sin_port = htons(port);
    srv_addr.sin_addr.s_addr = htonl(ip_init);
    memset(&(srv_addr.sin_zero), 0, 8);

     //connect to socket or open socket
    s_socket = socket(domain, service, protocol);

    //test connection or opened socket success
    test_connection (s_socket);
  
    //socket Option activating
    int n_opt_val = 1;
    int n_opt_len = sizeof(n_opt_val);
    int set_ret = setsockopt(s_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&n_opt_val, n_opt_len);
	test_connection (set_ret);
  
    //socket Type activating
        /*TODO*/
    //int opt_val = 0; 
    //int type_ret = ioctl(s_socket, FIONBIO,(char *) &opt_val);
    //test_connection (type_ret);


}

void Socket::test_connection (int conn){
    if (conn < 0){
        WSACleanup(); // only for windows
        perror("Connection Faild!!!!");
        exit(EXIT_FAILURE);
    }
}

//getter
int Socket::get_socket(){
    return s_socket;
}
struct sockaddr_in Socket::get_srv_addr (){
    return srv_addr;
}
 int Socket::get_conn(){
     return connection;
 }
//setter
void Socket::set_conn(int conn){
    connection = conn;
}
