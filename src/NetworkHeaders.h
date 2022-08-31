#ifndef NETWORKHEADERS_H
#define NETWORKHEADERS_H


#include <iostream>
// #include <sys/ioctl.h>
// #include <sys/types.h> 
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <sys/time.h>
// #include <sys/select.h>
// #include <netdb.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <iomanip>

namespace WebSocket{

        //frame
        enum WebsocketFrameSize {

            SmallFrame = 125,
            MeduimFrame = 126,
            BigFrame = 127

        };
        //data stream
        enum WebsocketDataStream {

            SmallStream = 2,
            MeduimStream = 4,
            BigStream = 10
        };

        enum SocketStatus{

            SocketClose = 0,
            SocketOpen = 1
        };
  
  
	//static bool client_atomic = false;
    static const std::string KMagicString  {"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"}; 
    static const std::string KWebsocketKey {"Sec-WebSocket-Key:"};
    static const std::string KGetRequest   {"GET / "};  
    static const std::string KGetFavicon   {"GET /f"};
    static const std::string KGetEndPoint  {"GET /chat"};
    static const std::string KHtmlFilePath {"..//indexpage//CarMonitor.html"};
    static const std::string KBase64Chars {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
    static const size_t KHttpCloseReq = 8;
    static const size_t KTcpCloseReq = 0;

};

#endif