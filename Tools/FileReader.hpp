#ifndef WEBSERVER_FILEREADER_HPP
#define WEBSERVER_FILEREADER_HPP

#include "Tools/Helper.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <sys/poll.h>
#include <unistd.h>


class FileReader {

public:
    static std::string readFile(const std::string& fileName);

    static std::string readFileDescriptor(int fd, size_t bufferSize);

    static void deleteFile(const std::string& fileName);

    static std::string findBetween(const std::string& path, const std::string& start = "", const std::string& stop = "");

    static std::string findFile(const std::string& path);

    static std::string findFileExt(const std::string& path);

    static std::string findQuery(const std::string& path);

    static std::string removeQuery(const std::string& path);

};


#endif //WEBSERVER_FILEREADER_HPP
