#include "WebServer.hpp"

ConfigServer* WebServer::configInstance = nullptr;

WebServer::WebServer(ConfigServer* config) {
    setConfig(config);
    this->socketServer = new SocketServer(config->listen);
    std::cout << "WebServer: Ready" << std::endl;
}

WebServer::WebServer(const WebServer& other) : socketServer(other.socketServer) {}

WebServer::~WebServer() {
    delete socketServer;
}

WebServer& WebServer::operator=(const WebServer& rhs) {
    socketServer = rhs.socketServer;
    return *this;
}

void WebServer::start() {
    while (true) {
        SocketClient* client = nullptr;
        HttpRequest* request = nullptr;
        HttpResponse* response = nullptr;

        try {
            std::cout << "--------------" << std::endl;
            std::cout << "WebServer: Waiting for connection..." << std::endl;

            client = socketServer->accept();
            std::cout << "WebServer: Connection accepted" << std::endl;

            std::string str = client->readAll();
            request = new HttpRequest(str);
            std::cout << "WebServer: Request " << request->getParams()->getUri() << std::endl;
            response = new HttpResponse(request);

            client->send(response->toString());
            std::cout << "WebServer: Response send" << std::endl;

            std::cout << "WebServer: Connection closed" << std::endl;
        } catch (const std::exception &) {
            std::cout << "WebServer: Connection rejected" << std::endl;
        }

        delete request;
        delete response;
        delete client;
    }
}

ConfigServer* WebServer::getConfig() {
    return configInstance;
}

void WebServer::setConfig(ConfigServer* config) {
    WebServer::configInstance = config;
}
