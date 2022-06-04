#ifndef WEBSERVER_HTTPHEADERS_HPP
#define WEBSERVER_HTTPHEADERS_HPP

#include "Tools/Helper.hpp"
#include "Tools/FileReader.hpp"
#include "Http/HttpConstants.hpp"
#include <vector>
#include <string>
#include <sstream>


class HttpHeaders {

public:
    HttpHeaders();

    HttpHeaders(const std::string& parse, const std::string& nlSep = NL_SEP, const std::string& headerSep = HEADERS_SEP);

    /*
     * const std::string& path - path to file from site folder
     * const std::string& content - content of the file
     */
    HttpHeaders(const std::string& path, const std::string& content, bool createFile);

    HttpHeaders(const HttpHeaders& other);

    virtual ~HttpHeaders();

    HttpHeaders& operator=(const HttpHeaders& rhs);

public:
    const std::vector<std::pair<std::string, std::string> >& getHeadersList() const;

    std::string getHeaderValue(const std::string& name) const;

    std::string toString() const;

    char** toEnv() const;

private:
    std::vector<std::pair<std::string, std::string> > headers;

};


#endif //WEBSERVER_HTTPHEADERS_HPP
