#ifndef WEBSERVER_WEBSERVER_HPP
#define WEBSERVER_WEBSERVER_HPP

#include "Web/SocketServer.hpp"
#include "Http/HttpRequest.hpp"
#include "Http/HttpResponse.hpp"
#include "Config/ConfigServer.hpp"
#include "Tools/FileReader.hpp"


class WebServer {

public:
    WebServer(ConfigServer* config);

    WebServer(const WebServer& other);

    virtual ~WebServer();

    WebServer& operator=(const WebServer& rhs);

public:
    void start();

    static ConfigServer* getConfig();

    static void setConfig(ConfigServer* config);

private:
    SocketServer* socketServer;
    static ConfigServer* configInstance;

};


#endif //WEBSERVER_WEBSERVER_HPP
