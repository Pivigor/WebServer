#include "Parser.hpp"

int main() {
    try {
        Parser parse("big.conf");

        for (std::vector<ConfigServer>::size_type i = 0; i < parse.servers.size(); i++) {
            std::cout << "Listen directive: " << parse.servers[i].listen << "\n"
                      << "Server_name: " << parse.servers[i].server_name << "\n"
                      << "host_name: " << parse.servers[i].host_name << std::endl;
        }

        for (std::vector<ConfigServer>::size_type i = 0; i < parse.servers.size(); i++) {
            std::map<std::string, LocationInfo>::const_iterator it = parse.servers[i].locations.begin();
            for (; it != parse.servers[i].locations.end(); ++it) {
                std::cout << " Locations: " << it->first << "\t"
                          << " Autoindex: " << it->second.autoindex
                          << " Body size: " << it->second.body_size
                          << " Index: " << it->second.index
                          << " Location_name: " << it->second.location_name
                          << " root: " << it->second.root
                          << " upload path: " << it->second.upload_path
                          << std::endl;
            }

            std::cout << "\n--- CGI ---\n";
            std::map<std::string, std::string>::const_iterator it2 = parse.servers[i].cgi.begin();
            for (; it2 != parse.servers[i].cgi.end(); ++it2) {
                std::cout << it2->first << "|" << it2->second << std::endl;
            }
        }
    }
    catch (const std::exception &) {
        std::cout << "Error caught while parsing config" << std::endl;
    };

}