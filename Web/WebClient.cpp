#include "WebClient.hpp"

WebClient::WebClient(const std::string& ip, int port) {
    this->socketClient = new SocketClient(ip, port);
    std::cout << "WebClient: Ready" << std::endl;
}

WebClient::WebClient(const WebClient& other) : socketClient(other.socketClient) {}

WebClient::~WebClient() {
    delete socketClient;
}

WebClient& WebClient::operator=(const WebClient& rhs) {
    socketClient = rhs.socketClient;
    return *this;
}

std::string WebClient::httpGet(const std::string& host) const {
    std::string request = "GET / HTTP/1.0\n"
                          "Host: " + host + "\n"
                          "\n";

    socketClient->send(request);
    return socketClient->readAll();
}
