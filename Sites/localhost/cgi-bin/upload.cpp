#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> splits;

    size_t last = 0;
    size_t next = 0;
    while ((next = str.find(delimiter, last)) != std::string::npos) {
        splits.push_back(str.substr(last, next - last));
        last = next + delimiter.size();
    }
    splits.push_back(str.substr(last));
    return splits;
}

std::string findQuery(char** env) {
    size_t i = 0;
    while (env[i] != nullptr) {
        std::string temp(env[i]);
        if (temp.find("QUERY_STRING") != -1) {
            std::vector<std::string> parse = split(temp, "=");
            if (parse[0] == "QUERY_STRING") {
                return temp.erase(0, 14);
            }
        }
        i++;
    }
    return "";
}

std::string parseQuery(char** env) {
    std::string query = findQuery(env);
    if (!query.empty()) {
        std::vector<std::string> parse = split(query, "&");
        if (parse.size() == 2) {
            std::vector<std::string> arg1 = split(parse[0], "=");
            std::vector<std::string> arg2 = split(parse[1], "=");
            if (arg1.size() == 2 && arg2.size() == 2) {
                std::cout << "DEBUG: " << arg1[1] << " " << arg2[1] << std::endl;
                return arg1[1];
            }
        }
    }

    return "";
}

std::string generateName() {
    std::stringstream nameBuilder;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    nameBuilder << "upload"
                << now->tm_year + 1900 << "-"
                << now->tm_mon + 1 << "-"
                << now->tm_mday << "T"
                << now->tm_hour << "-"
                << now->tm_min << "-"
                << now->tm_sec << ".txt";
    return nameBuilder.str();
}

void saveFile(const std::string& fileName) {
    if (!fileName.empty()) {
        std::ofstream outfile(fileName);

        std::cout << "Start uploading: " << std::endl;

        std::cin.sync();
        char c;
        while ((c = std::cin.get()) != '\0') {
            outfile << c;
        }

        outfile.close();

        std::cout << "\nUPLOAD OK!" << std::endl;
    }
}

int main(int argc, char** argv, char** env) {
    std::string uploadDir = "/Users/jgarlic/Desktop/Projects/Applications/C/SpeedRun/jgarlic-speedrun/Webserver/Sites/localhost/upload/";

    std::string query = parseQuery(env);
    std::string fileName;
    if (query.empty()) {
        fileName = uploadDir + generateName();
        std::cout << "DEBUG: " << fileName << std::endl;
    } else {
        fileName = uploadDir + query;
    }

    saveFile(fileName);
}
