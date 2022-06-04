#ifndef WEBSERVER_HTTPREQUEST_HPP
#define WEBSERVER_HTTPREQUEST_HPP

#include "Http/HttpRequestParams.hpp"
#include "Http/HttpHeaders.hpp"
#include "Http/HttpConstants.hpp"


class HttpRequest {

public:
    HttpRequest(const std::string& request, const std::string& bodySep = BODY_SEP, const std::string& nlSep = NL_SEP);

    HttpRequest(const HttpRequest& other);

    virtual ~HttpRequest();

    HttpRequest& operator=(const HttpRequest& rhs);

public:
    HttpRequestParams* getParams() const;

    HttpHeaders* getHeaders() const;

    const std::string& getBody() const;

    std::string getPath() const;

private:
    HttpRequestParams* params;
    HttpHeaders* headers;
    std::string body;

};


#endif //WEBSERVER_HTTPREQUEST_HPP
