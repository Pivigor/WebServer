#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string& ip, int port) : sock(0) {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "Client: Socket creation error" << std::endl;
        throw std::exception();
    }

    struct sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cout << "Client: Invalid address / Address not supported" << std::endl;
        throw std::exception();
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Client: Connection Failed" << std::endl;
        throw std::exception();
    }
}

SocketClient::SocketClient(int client_fd) : sock(client_fd) {}

SocketClient::SocketClient(const SocketClient& other) : sock(other.sock) {}

SocketClient::~SocketClient() {
    close(sock);
}

SocketClient& SocketClient::operator=(const SocketClient& rhs) {
    sock = rhs.sock;
    return *this;
}

std::string SocketClient::readAll() const {
    return FileReader::readFileDescriptor(sock, BUFFER_SIZE);
}

void SocketClient::send(const std::string& message) const {
    ::send(sock, message.c_str(), message.size(), 0);
}
