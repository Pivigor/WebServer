#ifndef WEBSERVER_HELPER_HPP
#define WEBSERVER_HELPER_HPP

#include <string>
#include <vector>


class Helper {

public:
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);

    static size_t count(const std::string& str, const std::string& word);

    static std::string toLower(const std::string& str);

};


#endif //WEBSERVER_HELPER_HPP
