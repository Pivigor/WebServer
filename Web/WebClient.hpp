#ifndef WEBSERVER_WEBCLIENT_HPP
#define WEBSERVER_WEBCLIENT_HPP

#include "Web/SocketClient.hpp"


class WebClient {

public:
    WebClient(const std::string& ip, int port);

    WebClient(const WebClient& other);

    virtual ~WebClient();

    WebClient& operator=(const WebClient& rhs);

public:
    std::string httpGet(const std::string& host) const;

private:
    SocketClient* socketClient;

};


#endif //WEBSERVER_WEBCLIENT_HPP
