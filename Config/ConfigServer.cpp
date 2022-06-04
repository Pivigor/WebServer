//
// Created by polya on 5/16/22.
//

#include "ConfigServer.hpp"


ConfigServer::ConfigServer() { // check in the func if the params are nullptr, then throw ex

    this->listen = 0;
//    this->server_name = nullptr; // check whether there are no duplicates in server_name NOT OBLIGATORY PARAM
//    this->host_name = nullptr;
//    this->cgi[nullptr] = nullptr;
//    this->locations[nullptr] = LocationInfo();

}
ConfigServer::~ConfigServer() {
}

ConfigServer& ConfigServer::operator=(ConfigServer const &obj) {
    if (this == &obj) {
        return *this;
    }

    this->listen = obj.listen;
    this->server_name = obj.server_name;
    this->host_name = obj.host_name;
    this->cgi = obj.cgi;
    this->locations = obj.locations;

    return *this;
}

ConfigServer::ConfigServer(ConfigServer const &obj) {
    *this = obj;
}

std::string ConfigServer::findCGI(const std::string& fileExt) {
    std::map<std::string, std::string>::const_iterator it = cgi.begin();
    for (; it != cgi.end(); ++it) {
        if (FileReader::findFileExt(it->first) == fileExt) {
            return it->second;
        }
    }
    return "";
}

LocationInfo* ConfigServer::findLocation(const std::string &uri) {
    std::map<std::string, LocationInfo>::const_iterator it = locations.begin();
    for (; it != locations.end(); ++it) {
        if (it->first == uri) {
            return const_cast<LocationInfo *>(&it->second);
        }
    }
    return nullptr;
}
