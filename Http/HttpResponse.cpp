#include "HttpResponse.hpp"

HttpResponse::HttpResponse(HttpRequest* request) {
    if (request->getParams()->getType() == HttpRequestParams::GET) {
        try {
            if (tryDefaultGetFile(request) || tryCGI(request) || tryGetFile(request)) {
                std::cout << "WebServer: HTTP/1.1 200 OK" << std::endl;
                params = "HTTP/1.1 200 OK\n";
                headers = new HttpHeaders(request->getPath(), body, true);
            } else {
                throw std::exception();
            }
        } catch (const std::exception &) {
            std::cout << "WebServer: HTTP/1.1 404 Not Found" << std::endl;
            params = "HTTP/1.1 404 Not Found\n";
            headers = new HttpHeaders();
        }
    } else if (request->getParams()->getType() == HttpRequestParams::POST) {
        try {
            if (tryCGI(request)) {
                std::cout << "WebServer: HTTP/1.1 200 OK" << std::endl;
                params = "HTTP/1.1 200 OK\n";
                headers = new HttpHeaders(request->getPath(), body, true);
            } else {
                throw std::exception();
            }
        } catch (const std::exception &) {
            std::cout << "WebServer: HTTP/1.1 404 Not Found" << std::endl;
            params = "HTTP/1.1 404 Not Found\n";
            headers = new HttpHeaders();
        }
    } else if (request->getParams()->getType() == HttpRequestParams::DELETE) {
        try {
            FileReader::deleteFile(request->getPath());
            std::cout << "WebServer: HTTP/1.1 200 OK" << std::endl;
            params = "HTTP/1.1 200 OK\n";
            headers = new HttpHeaders(request->getPath(), body, true);
        } catch (const std::exception &) {
            std::cout << "WebServer: HTTP/1.1 404 Not Found" << std::endl;
            params = "HTTP/1.1 404 Not Found\n";
            headers = new HttpHeaders();
        }
    }
}

HttpResponse::HttpResponse(const HttpResponse& other) : params(other.params),
                                                        headers(other.headers),
                                                        body(other.body) {}

HttpResponse::~HttpResponse() {
    //delete params;
    delete headers;
}

HttpResponse& HttpResponse::operator=(const HttpResponse& rhs) {
    params = rhs.params;
    headers = rhs.headers;
    body = rhs.body;
    return *this;
}

std::string HttpResponse::toString() const {
    return params + headers->toString() + body;
}

bool HttpResponse::tryDefaultGetFile(HttpRequest* request) {
    std::string serverName = WebServer::getConfig()->server_name;
    LocationInfo* locationInfo = WebServer::getConfig()->findLocation(request->getParams()->getUri());
    if (request->getHeaders()->getHeaderValue("Host") == serverName && locationInfo != nullptr && !locationInfo->index.empty()) {
        body = FileReader::readFile(serverName + locationInfo->index);
        request->getParams()->setUri(locationInfo->index);
        return true;
    }
    return false;
}

bool HttpResponse::tryCGI(HttpRequest* request) {
    std::string serverName = WebServer::getConfig()->server_name;
    std::string cgi = WebServer::getConfig()->findCGI(FileReader::findFileExt(request->getPath()));
    LocationInfo* locationInfo = WebServer::getConfig()->findLocation("/cgi-bin");
    if (!cgi.empty()) {
        body = CGI::executeCGI(cgi,
                               FileReader::removeQuery(request->getPath()),
                               FileReader::findQuery(request->getPath()),
                               request->getBody());
        request->getParams()->setUri(".html");  //TODO: refactor this lines
        return true;
    } else if (request->getHeaders()->getHeaderValue("Host") == serverName && locationInfo != nullptr && request->getParams()->getUri().find("/cgi-bin") != (size_t) -1) {
        body = CGI::executeCGI(FileReader::removeQuery(request->getPath()),
                               "",
                               FileReader::findQuery(request->getPath()),
                               request->getBody());
        //request->getParams()->setUri(".html");
        return true;
    }  else if (FileReader::findFileExt(request->getPath()) == "env") {
        body = CGI::executeCGI("env",
                               "",
                               FileReader::findQuery(request->getPath()));
        request->getParams()->setUri(".html");
        return true;
    } else if (FileReader::findFileExt(request->getPath()) == "cat") {
        body = CGI::executeCGI("cat",
                               "",
                               "",
                               request->getBody());
        request->getParams()->setUri(".html");
        return true;
    } else if (FileReader::findFileExt(request->getPath()) == "delete") {
        body = CGI::executeCGI("rm",
                               FileReader::removeQuery(request->getPath()));
        //request->getParams()->setUri(".html");
        return true;
    }
    return false;
}

bool HttpResponse::tryGetFile(HttpRequest* request) {
    body = FileReader::readFile(request->getPath());
    return true;
}
