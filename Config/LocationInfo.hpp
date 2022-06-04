//
// Created by polya on 5/16/22.
//

#ifndef JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_LOCATIONINFO_HPP
#define JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_LOCATIONINFO_HPP
#include <iostream>
#include <vector>
#include <map>


class LocationInfo {

public:
    std::string root;
    std::string location_name;
    bool autoindex;
    int body_size;
    std::vector<std::string> allowed_methods;
    std::string index;
    std::string upload_path;
    std::map<int, std::string> error_page;
    std::map<int, std::string> return_page;

public:
    LocationInfo();
    LocationInfo(LocationInfo const &obj);
//    LocationInfo(LocationInfo *obj);
    LocationInfo& operator=(LocationInfo const &obj);
    ~LocationInfo();
    // make assign and copy constructor
};


#endif //JGARLIC_SPEEDRUN_JGARLIC_WEBSERVER_LOCATIONINFO_HPP
