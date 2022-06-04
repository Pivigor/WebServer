#ifndef WEBSERVER_HTTPRESPONSE_HPP
#define WEBSERVER_HTTPRESPONSE_HPP

#include "Web/WebServer.hpp"
#include "Http/HttpRequest.hpp"
#include "Tools/FileReader.hpp"
#include "Tools/CGI.hpp"


class HttpResponse {

public:
    HttpResponse(HttpRequest* request);

    HttpResponse(const HttpResponse& other);

    virtual ~HttpResponse();

    HttpResponse& operator=(const HttpResponse& rhs);

public:
    std::string toString() const;

private:
    bool tryDefaultGetFile(HttpRequest* request);

    bool tryCGI(HttpRequest* request);

    bool tryGetFile(HttpRequest* request);

private:
    std::string params;
    HttpHeaders* headers;
    std::string body;

};


#endif //WEBSERVER_HTTPRESPONSE_HPP
