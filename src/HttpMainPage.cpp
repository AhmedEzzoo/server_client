#include "HttpMainPage.h"
#include <cassert>
//Default constructor
HttpMainPage::HttpMainPage(){

    http_header_prepare();
    ws_header_prepare();
    http_page_prepare();
}

void HttpMainPage::ws_header_prepare(){

    std::ostringstream oss;
     oss << "HTTP/1.1 101 Switching Protocols\r\n"
         << "Upgrade: websocket\r\n"
         << "Connection: upgrade\r\n"
         << "Sec-WebSocket-Accept: ";
        

        //header to send
        ws_header = oss.str();
}

void HttpMainPage::http_header_prepare (){
    std::ostringstream ss;
     ss << "HTTP/1.1 200 OK\r\n"
        << "Connection: keep-alive\r\n"
        << "Content-Type: text/html\r\n"
        << "\r\n";

        //header to send
        http_header = ss.str();
}

void HttpMainPage::http_page_prepare() {

      //main page data
      std::string line;
      std::stringstream page_ss;

     //open the main page file
     std::ifstream file_stream (KHtmlFilePath);

     if (file_stream.is_open()){

     while (std::getline(file_stream, line)){
              page_ss << line;
          }

          http_page_stream = page_ss.str();
     }
          file_stream.close();
}

std::string HttpMainPage::base64_encode( char const* bytes_to_encode, unsigned int in_len) {

  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += KBase64Chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += KBase64Chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

//getter
std::string HttpMainPage::get_http_page(){
    return http_page_stream;
}

std::string HttpMainPage::get_http_header(){
    return http_header;
}

std::string HttpMainPage::get_ws_header(){
    return ws_header;
}