#ifndef WEBSERVER_SOCKETSERVER_HPP
#define WEBSERVER_SOCKETSERVER_HPP

#include <netinet/in.h>
#include "Web/SocketClient.hpp"


class SocketServer {

public:
    SocketServer(int port);

    SocketServer(const SocketServer& other);

    virtual ~SocketServer();

    SocketServer& operator=(const SocketServer& rhs);

public:
    SocketClient* accept();

private:
    int server_fd;
    struct sockaddr_in address;
    int addrlen;

};


#endif //WEBSERVER_SOCKETSERVER_HPP
