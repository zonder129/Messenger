#ifndef SERVER_H
#define SERVER_H
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "server.h"
#include "python_connect.h"

#define SERVER_PORT 8080
#define BUFF_SIZE 1024
#define ERROR_STR "error"

using namespace boost::asio;
using namespace boost::posix_time;
using boost::system::error_code;
class server
{
public:
    server();
    void handle_connections();
private:
    size_t read_complete(char * buff, const error_code & err, size_t bytes);
    char *create_answer(char*);
    python_connect p;
};


#endif // SERVER_H
