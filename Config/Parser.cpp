//
// Created by polya on 5/15/22.
//

#include "Parser.hpp"

Parser::Parser() {

    config_file.open("big.conf", std::fstream::in);
    ParseServer();
}

Parser::Parser(std::string filename) {

    config_file.open(filename, std::fstream::in);
    ParseServer();

}

Parser::~Parser() {
    config_file.close();
}

bool isSpace(unsigned char c) {
    return (c == '\n' || c == '\r' || c == '\t'
             || c == '\v' || c == '\f');
}

void Parser::ParseServer() {

    std::string block_name;
    ConfigServer *new_server = nullptr;
    LocationInfo *location_vector_elem = nullptr;
    int location_flag = 0;
    std::string line;

    while (std::getline(config_file, line) ) {

        std::string delimiter = " ";
        std::vector<std::string> words;

//        std::cout << "LINE:" << std::endl;

//        std::cout << line << std::endl;
        size_t pos = 0;

        if (line == "") {
            continue ;
        }

//        std::cout << line << std::endl;

        std::string::iterator iter;
        iter = line.begin();

        while ( iter != line.end() ) {
            if (isSpace(*(iter) ) ) {
                line.replace(iter, iter + 1, 1, ' ');
            }
            iter++;
        }

        while ((pos = line.find(delimiter)) != std::string::npos) {

            words.push_back( line.substr(0, pos) );
//            std:: cout << line.substr(0, pos) << std::endl;
            line.erase(0, pos + delimiter.length());
        }

        words.push_back(line.substr(0, line.length()));

//        std::cout << line << std::endl;

//        std::cout << "TOKENS:" << std::endl;

        std::vector<std::string>::iterator it = words.begin();

        while (it != words.end()) {
            if (*it == " " || *it == "" || *it == " ") {
                words.erase(it);
                continue ;
            }
            it++;
        }

//        for (size_t i = 0; i < words.size(); i++) {
//            std::cout << i << ". " + words[i] << std::endl;
//        }

        if (words[0] == "#") {
            continue ;
        }
        else if (words[words.size() - 1] == "{") {
//            std::cout << "HERE" << std::endl;
            if (words[0] == "server") {
                if (words.size() > 2) {
                    throw MyException();
                }
                block_name = "server";
                new_server = new ConfigServer;

            }
            else if (words[0] == "location") {
                if (words.size() > 3) {
                    throw MyException();
                }
                block_name = "location";
//                if (location_vector_elem != nullptr) {
//                    location_vector_elem = new LocationInfo(location_vector_elem.);
//                    std::cout << location_vector_elem->location_name << std::endl;
//                }
//                else {
                location_vector_elem = new LocationInfo();
//                }
                location_vector_elem->location_name = words[1];
                location_flag = 0;
            }
            else {
                throw MyException();
            }
        }
        else if (words[words.size() - 1][words[words.size() - 1].size() - 1] == ';' || words[words.size() - 1] == ";") {

            if (words[words.size() - 1] == ";") {
                words.pop_back();
            }
            else if (words[words.size() - 1][words[words.size() - 1].size() - 1] == ';') {
                words[words.size()-1].erase(words[words.size() - 1].size() - 1, 1);
            }

            if (words.size() < 2 || words.size() > 4) {
                throw MyException();
            }
            if (block_name == "server") {

                if (words[0] == "server_name") {
//                    std::cout << "SERVER_NAME" << std::endl;
                    new_server->server_name = words[words.size() - 1];

                }
                else if (words[0] == "host") {
//                    std::cout << "HOST_NAME" << std::endl;
                    new_server->host_name = words[words.size() - 1];

                }
                else if (words[0] == "listen") {
//                    std::cout << "LISTEN" << std::endl;
                    new_server->listen = atoi(words[words.size() - 1].c_str());
                }
                else if (words[0] == "cgi") {
//                    std::cout << "CGI" << std::endl;
                    new_server->cgi.insert(std::make_pair(words[words.size() - 2], words[words.size() - 1]));
                }
                else {
                    throw MyException();
                }
            }
            else if (block_name == "location") {

                if (words[0] == "root") { // add size checking
//                    std::cout << "ROOT" << std::endl;
                    location_vector_elem->root = words[words.size() - 1];

                }
                else if (words[0] == "index") {
//                    std::cout << "INDEX" << std::endl;
                    location_vector_elem->index = words[words.size() - 1];

                }
                else if (words[0] == "upload_path") {
//                    std::cout << "UPLOAD_PATH" << std::endl;
                    location_vector_elem->upload_path = words[words.size() - 1];

                }
                else if (words[0] == "autoindex") {
//                    std::cout << "AUTOINDEX" << std::endl;

                    if (words[1] == "on") {
                        location_vector_elem->autoindex = 1;
                    }
                    else if (words[1] == "off") {
                        location_vector_elem->autoindex = 0;
                    }
                    else {
                        throw MyException();
                    }
                }
                else if (words[0] == "body_size") {

//                    std::cout << "BODY_SIZE" << std::endl;

                    location_vector_elem->body_size = atoi(words[words.size() - 1].c_str());
                }
                else if (words[0] == "allow_methods") {

//                    std::cout << "ALLOWED_METHODS" << std::endl;

                    if (words.size() > 4) {
                        throw MyException();
                    }
                    for (std::size_t i = 1; i < words.size(); i++) {
                        location_vector_elem->allowed_methods.push_back(words[i]);
                    }
                }
                else if (words[0] == "error_page") {

//                    std::cout << "ERROR_PAGE" << std::endl;

                    location_vector_elem->error_page.insert(std::make_pair(atoi( words[words.size() - 2].c_str() ), words[words.size() - 1]));
                }
                else if (words[0] == "return") {

//                    std::cout << "RETURN" << std::endl;

                    location_vector_elem->return_page.insert( std::make_pair(atoi( words[words.size() - 2].c_str() ), words[words.size() - 1]) );
                }
                else {
                    throw MyException();
                }
            }
        }
        else if (words[0] == "}" && words.size() == 1 && block_name == "location") {
//            std::cout << "HERE" << std::endl;
//            std::cout << block_name << std::endl;
            block_name.clear();
            new_server->locations.insert(std::make_pair(location_vector_elem->location_name, *location_vector_elem));

            if (location_vector_elem != nullptr) {
                delete location_vector_elem;
            }
            location_flag = 1;
            continue ;
        }
        else if (words[0] == "}" && words.size() == 1 && location_flag == 1) {
//            std::cout << "THERE" << std::endl;
//            std::cout << block_name << std::endl;
            servers.push_back(*new_server);
            delete new_server;
            location_flag = 0;
            continue ;
        }
        else {
            throw MyException();
        }
        line.clear();
    }
}

std::vector<ConfigServer> Parser::GetConfig() {
    return servers;
}
