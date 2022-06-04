#include "SocketServer.hpp"

SocketServer::SocketServer(int port) {
    int opt = 1;
    addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Server: socket failed");
        throw std::exception();
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR /*| SO_REUSEPORT*/, &opt, sizeof(opt))) {
        perror("Server: setsockopt");
        throw std::exception();
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("Server: bind failed");
        throw std::exception();
    }
    if (listen(server_fd, 3) < 0) {
        perror("Server: listen");
        throw std::exception();
    }
}

SocketServer::SocketServer(const SocketServer& other) : server_fd(other.server_fd),
                                                        address(other.address),
                                                        addrlen(other.addrlen) {}

SocketServer::~SocketServer() {
    close(server_fd);
}

SocketServer& SocketServer::operator=(const SocketServer& rhs) {
    server_fd = rhs.server_fd;
    address = rhs.address;
    addrlen = rhs.addrlen;
    return *this;
}

SocketClient* SocketServer::accept() {
    int new_socket;
    if ((new_socket = ::accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
        perror("Server: accept");
        throw std::exception();
    }
    return new SocketClient(new_socket);
}
