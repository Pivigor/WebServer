#include "Helper.hpp"

std::vector<std::string> Helper::split(const std::string& str, const std::string& delimiter) {
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

size_t Helper::count(const std::string& str, const std::string& word) {
    size_t count = 0;

    size_t last = 0;
    size_t next = 0;
    while ((next = str.find(word, last)) != std::string::npos) {
        count++;
        last = next + 1;
    }
    return count;
}

std::string Helper::toLower(const std::string &str) {
    std::string lowered;
    for (size_t i = 0; i < str.size(); i++) {
        lowered.push_back((char) std::tolower(str[i]));
    }
    return lowered;
}
