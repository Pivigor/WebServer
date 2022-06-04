#ifndef WEBSERVER_HTTPREQUESTPARAMS_HPP
#define WEBSERVER_HTTPREQUESTPARAMS_HPP

#include <ostream>
#include "Tools/Helper.hpp"


class HttpRequestParams {

public:
    HttpRequestParams();

    HttpRequestParams(const std::string& params);

    HttpRequestParams(const HttpRequestParams& other);

    virtual ~HttpRequestParams();

    HttpRequestParams& operator=(const HttpRequestParams& rhs);

    enum HttpRequestType {
        GET,
        POST,
        DELETE
    };

public:
    HttpRequestType getType() const;

    void setType(HttpRequestType newType);

    const std::string &getUri() const;

    void setUri(const std::string &newUri);

    const std::string &getAProtocol() const;

    void setAProtocol(const std::string &newProtocol);

    friend std::ostream &operator<<(std::ostream &os, const HttpRequestParams &parameters);

private:
    HttpRequestType type;
    std::string uri;
    std::string protocol;

};


#endif //WEBSERVER_HTTPREQUESTPARAMS_HPP
