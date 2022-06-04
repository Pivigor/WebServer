//
// Created by polya on 5/16/22.
//

#ifndef JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_CONFIGSERVER_HPP
#define JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_CONFIGSERVER_HPP


#include "Config/LocationInfo.hpp"
#include "Tools/FileReader.hpp"


class ConfigServer {

public:
    int listen;
    std::string server_name;
    std::string host_name;
    std::map<std::string, std::string> cgi;
    std::map<std::string, LocationInfo> locations;

    ConfigServer();
    ConfigServer& operator=(ConfigServer const &obj);
    ConfigServer(ConfigServer const &obj);
    virtual ~ConfigServer();

public:
    std::string findCGI(const std::string& fileExt);

    LocationInfo* findLocation(const std::string& uri);

};

// check the duplicates

#endif //JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_CONFIGSERVER_HPP
