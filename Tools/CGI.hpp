#ifndef WEBSERVER_CGI_HPP
#define WEBSERVER_CGI_HPP

#include "Http/HttpRequest.hpp"
#include "Tools/FileReader.hpp"
#include <unistd.h>
#include <iostream>


class CGI {

public:
    static std::string executeCGI(const std::string& app, const std::string& arg = "", const std::string& query = "", const std::string& body = "");

    static char** appendEnv(char** envToAppend);

    static size_t sizeEnv(char** env);

};


#endif //WEBSERVER_CGI_HPP
