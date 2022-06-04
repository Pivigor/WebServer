#ifndef WEBSERVER_SOCKETCLIENT_HPP
#define WEBSERVER_SOCKETCLIENT_HPP

#include "Tools/FileReader.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

#define BUFFER_SIZE 1024


class SocketClient {

public:
    SocketClient(const std::string& ip, int port);

    SocketClient(int client_fd);

    SocketClient(const SocketClient& other);

    virtual ~SocketClient();

    SocketClient& operator=(const SocketClient& rhs);

public:
    std::string readAll() const;

    void send(const std::string& message) const;

private:
    int sock;

};


#endif //WEBSERVER_SOCKETCLIENT_HPP
