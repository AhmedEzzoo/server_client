#ifndef HTTPMAINPAGE_H
#define HTTPMAINPAGE_H

#include "NetworkHeaders.h"

#define SIZE 1000

using namespace WebSocket;
class HttpMainPage {


    public :
        
        //constructor
        HttpMainPage();

        //to encode the accept web socket key
        std::string base64_encode( char const* bytes_to_encode, unsigned int in_len);
        
        //getter
        std::string get_http_page();

        std::string get_http_header();

        std::string get_ws_header();
        
    private :

        //header prepare to send
        void http_header_prepare();

        //page prepare to send
        void http_page_prepare();

        //websocket header to response
        void ws_header_prepare();

        //header string
        std::string http_header;

        //page string prepare
        std::string http_page_stream;

        //websocket header prepare
        std::string ws_header;

};

#endif