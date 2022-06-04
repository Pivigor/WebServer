#include "HttpRequest.hpp"

HttpRequest::HttpRequest(const std::string& request, const std::string& bodySep, const std::string& nlSep) {
    size_t paramsIndex = request.find(nlSep);
    std::string paramsStr = request.substr(0, paramsIndex);
    params = new HttpRequestParams(paramsStr);

    size_t headersIndex = request.find(bodySep);
    std::string headersStr = request.substr(paramsIndex + nlSep.size(), headersIndex - paramsIndex - nlSep.size());
    headers = new HttpHeaders(headersStr);

    body = request.substr(headersIndex + bodySep.size(), request.size() - headersIndex - bodySep.size());
}

HttpRequest::HttpRequest(const HttpRequest& other) : params(other.params),
                                                     headers(other.headers),
                                                     body(other.body) {}

HttpRequest::~HttpRequest() {
    delete params;
    delete headers;
}

HttpRequest& HttpRequest::operator=(const HttpRequest& rhs) {
    params = rhs.params;
    headers = rhs.headers;
    body = rhs.body;
    return *this;
}

HttpRequestParams* HttpRequest::getParams() const {
    return params;
}

HttpHeaders* HttpRequest::getHeaders() const {
    return headers;
}

const std::string& HttpRequest::getBody() const {
    return body;
}

std::string HttpRequest::getPath() const {
    return getHeaders()->getHeaderValue("Host") + getParams()->getUri();
}
