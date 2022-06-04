#include <iostream>
#include "Web/WebServer.hpp"
#include "Config/Parser.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Bad args" << std::endl;
        exit(0);
    }

    Parser parse(argv[1]);
    if (parse.servers.size() != 1) {
        std::cout << "Bad config" << std::endl;
        exit(0);
    }

    ConfigServer* configServer = parse.servers.begin().base();

    WebServer* server = new WebServer(configServer);
    server->start();
    delete server;

}
