//
// Created by polya on 5/15/22.
//

#ifndef JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_ParseR_HPP
#define JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_ParseR_HPP

#include <istream>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Config/LocationInfo.hpp"
#include "Config/ConfigServer.hpp"

# define TAB 9

class Parser {

    // need to move it to the config class

public:
    std::vector<ConfigServer> servers;
    std::string block_name;
    std::fstream config_file;
    std::string base_string;
public:

    Parser();

    Parser(std::string filename);

    virtual ~Parser();

    void ParseServer();

    std::vector<ConfigServer> GetConfig();


    class MyException : public std::exception {
        const char *what () const throw () {
            return "Error while parsing config";
        }
    };

    // what errors to parse? e.g. the abscence of "/" in the location, would the server itself throw an error or should the parser do it?

};

bool isSpace(unsigned char c);

#endif //JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_ParseR_HPP
