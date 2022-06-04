#include "HttpHeaders.hpp"

HttpHeaders::HttpHeaders() {}

HttpHeaders::HttpHeaders(const std::string& parse, const std::string& nlSep, const std::string& headerSep) {
    std::vector<std::string> headersParse = Helper::split(parse, nlSep);
    for (std::vector<std::string>::iterator it = headersParse.begin(); it != headersParse.end(); it++) {
        std::vector<std::string> header = Helper::split(*it, headerSep);
        if (header.size() == 2) {
            headers.push_back(std::pair<std::string, std::string>(header[0], header[1]));
        } else {
            throw std::exception();
        }
    }
}

HttpHeaders::HttpHeaders(const std::string& path, const std::string& content, bool createFile) {
    headers.push_back(std::pair<std::string, std::string>("Connection", "close"));

    if (createFile || !content.empty()) {
        std::string fileExt = FileReader::findFileExt(path);
        if (fileExt == "htm" || fileExt == "html") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "text/html"));
        } else if (fileExt == "css") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "text/css"));
        } else if (fileExt == "jpg" || fileExt == "jpeg") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/jpeg"));
        } else if (fileExt == "png") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/png"));
        } else if (fileExt == "ico") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/x-icon"));
        } else if (fileExt == "gif") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/gif"));
        } else if (fileExt == "svg") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/svg+xml"));
        } else if (fileExt == "tiff") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "image/tiff"));
        } else if (fileExt == "js") {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "application/javascript"));
        } else {
            headers.push_back(std::pair<std::string, std::string>("Content-Type", "plain/text"));
        }

        headers.push_back(std::pair<std::string, std::string>("Content-Length", std::to_string(content.size())));
    }
}

HttpHeaders::HttpHeaders(const HttpHeaders& other) : headers(other.headers) {}

HttpHeaders::~HttpHeaders() {}

HttpHeaders& HttpHeaders::operator=(const HttpHeaders& rhs) {
    headers = rhs.headers;
    return *this;
}

const std::vector<std::pair<std::string, std::string> >& HttpHeaders::getHeadersList() const {
    return headers;
}

std::string HttpHeaders::getHeaderValue(const std::string& name) const {
    for (size_t i = 0; i < headers.size(); i++) {
        if (headers[i].first == name) {
            return headers[i].second;
        }
    }
    return std::string("");
}


std::string HttpHeaders::toString() const {
    std::stringstream str;
    for (size_t i = 0; i < headers.size(); i++) {
        str << headers[i].first << ": " << headers[i].second << "\n";
    }
    str << "\n";
    return str.str();
}

char** HttpHeaders::toEnv() const {
    char** env = new char*[headers.size() + 1];
    for (size_t i = 0; i < headers.size(); i++) {
        std::stringstream strBuilder;
        strBuilder << headers[i].first << "=" << headers[i].second;
        std::string str = strBuilder.str();

        env[i] = new char[str.size() + 1];
        for (size_t j = 0; j < str.size(); j++) {
            env[i][j] = str[j];
        }
        env[i][str.size()] = '\0';
    }
    env[headers.size()] = nullptr;
    return env;
}
