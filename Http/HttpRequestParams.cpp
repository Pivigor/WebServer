#include "HttpRequestParams.hpp"

HttpRequestParams::HttpRequestParams() {}

HttpRequestParams::HttpRequestParams(const std::string& params) {
    std::vector<std::string> parse = Helper::split(params, " ");
    if (parse.size() == 3) {
        if (parse[0] == "GET") {
            type = GET;
        } else if (parse[0] == "POST") {
            type = POST;
        } else if (parse[0] == "DELETE") {
            type = DELETE;
        } else {
            throw std::exception();
        }

        uri = std::string(parse[1]);
        protocol = std::string(parse[2]);

    } else {
        throw std::exception();
    }

}

HttpRequestParams::HttpRequestParams(const HttpRequestParams& other) : type(other.type),
                                                                       uri(other.uri),
                                                                       protocol(other.protocol) {}

HttpRequestParams::~HttpRequestParams() {}

HttpRequestParams& HttpRequestParams::operator=(const HttpRequestParams& rhs) {
    type = rhs.type;
    uri = rhs.uri;
    protocol = rhs.protocol;
    return *this;
}

HttpRequestParams::HttpRequestType HttpRequestParams::getType() const {
    return type;
}

void HttpRequestParams::setType(HttpRequestParams::HttpRequestType newType) {
    HttpRequestParams::type = newType;
}

const std::string& HttpRequestParams::getUri() const {
    return uri;
}

void HttpRequestParams::setUri(const std::string& newUri) {
    HttpRequestParams::uri = newUri;
}

const std::string& HttpRequestParams::getAProtocol() const {
    return protocol;
}

void HttpRequestParams::setAProtocol(const std::string& newProtocol) {
    protocol = newProtocol;
}

std::ostream& operator<<(std::ostream& os, const HttpRequestParams& parameters) {
    os << "type: " << parameters.type << " uri: " << parameters.uri << " protocol: " << parameters.protocol;
    return os;
}
