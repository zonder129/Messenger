#include "server.h"
io_service service;

server::server()
{
    p=python_connect();
}

size_t server::read_complete(char * buff, const error_code & err, size_t bytes) {
    if ( err) return 0;
    bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
    return found ? 0 : 1;
}

void server::handle_connections() {
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(),SERVER_PORT));
    char buff[BUFF_SIZE];
    while ( true) {
        ip::tcp::socket sock(service);
        acceptor.accept(sock);
        boost::system::error_code error;
        int bytes = sock.read_some(boost::asio::buffer(buff), error);
        if(bytes){
            char *answer = create_answer(buff);
            std::string msg(answer);
            sock.write_some(buffer(msg));
            sock.close();
        }else{
            std::string msg(ERROR_STR, strlen(ERROR_STR)*sizeof(ERROR_STR));
            sock.write_some(buffer(msg));
            sock.close();
        }
    }
}

char* server::create_answer(char *question){
    char *ans = p.getRezult(question);
    return ans;
}
