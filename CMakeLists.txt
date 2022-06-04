cmake_minimum_required(VERSION 3.21.1)
project(Webserver)

set(CMAKE_CXX_STANDARD 98)
include_directories(.)

add_executable(Webserver main.cpp
        Web/SocketClient.cpp Web/SocketClient.hpp
        Web/SocketServer.cpp Web/SocketServer.hpp
        Web/WebClient.cpp Web/WebClient.hpp
        Web/WebServer.cpp Web/WebServer.hpp
        Http/HttpRequest.cpp Http/HttpRequest.hpp
        Http/HttpRequestParams.cpp Http/HttpRequestParams.hpp
        Http/HttpHeaders.cpp Http/HttpHeaders.hpp
        Http/HttpResponse.cpp Http/HttpResponse.hpp
        Http/HttpConstants.hpp
        Config/Parser.cpp Config/Parser.hpp
        Config/ConfigServer.cpp Config/ConfigServer.hpp
        Config/LocationInfo.cpp Config/LocationInfo.hpp
        Tools/FileReader.cpp Tools/FileReader.hpp
        Tools/Helper.cpp Tools/Helper.hpp
        Tools/CGI.cpp Tools/CGI.hpp)
add_executable(Server Server.cpp)
add_executable(Client Client.cpp)
add_executable(Config Config/main.cpp
        Config/Parser.cpp Config/Parser.hpp
        Config/ConfigServer.cpp Config/ConfigServer.hpp
        Config/LocationInfo.cpp Config/LocationInfo.hpp
        Tools/FileReader.cpp Tools/FileReader.hpp
        Tools/Helper.cpp Tools/Helper.hpp)
