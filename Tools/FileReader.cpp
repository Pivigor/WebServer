#include "FileReader.hpp"

std::string FileReader::readFile(const std::string& fileName) {
    std::ifstream t(fileName);

    if (t.is_open()) {
        std::stringstream buffer;
        buffer << t.rdbuf();
        t.close();
        return buffer.str();
    } else {
        throw std::exception();
    }
}

std::string FileReader::readFileDescriptor(int fd, size_t bufferSize) {
    std::stringstream str;
    char buffer[bufferSize];
    std::fill(buffer, buffer + bufferSize, '\0');

    struct pollfd pfd[1];
    pfd[0].events = POLLIN;
    pfd[0].fd = fd;
    int retry = 0;
    size_t size;
    while(poll(pfd, 1, 100) == 1) {
        size = read(fd, buffer, bufferSize - 1);
        //std::cout << buffer;

        if (size < 0 || retry == 3) {
            break;
        } else if (size == 0) {
            retry++;
            continue;
        } else {
            retry = 0;
        }

        str << buffer;
        std::fill(buffer, buffer + bufferSize, '\0');
    }

    return str.str();
}

void FileReader::deleteFile(const std::string &fileName) {
    if (std::remove(fileName.c_str()) != 0) {
        throw std::exception();
    }
}

std::string FileReader::findBetween(const std::string& path, const std::string& start, const std::string& stop) {
    size_t extStartIndex = 0;
    if (!start.empty()) {
        extStartIndex = path.find_last_of(start);
        if (extStartIndex == (size_t) -1) {
            return "";
        } else {
            extStartIndex++;
        }
    }

    size_t extStopIndex = path.size();
    if (!stop.empty()) {
        extStopIndex = path.find_last_of(stop);
        if (extStopIndex == (size_t) -1) {
            extStopIndex = path.size();
        }
    }

    std::string between = path.substr(extStartIndex, extStopIndex - extStartIndex);
    return between;
}

std::string FileReader::findFile(const std::string& path) {
    return findBetween(path, "/", "?");
}

std::string FileReader::findFileExt(const std::string& path) {
    return Helper::toLower(findBetween(path, ".", "?"));
}

std::string FileReader::findQuery(const std::string &path) {
    std::string query = findBetween(path, "?");
    if (!query.empty()) {
        query.insert(0, "?");
    }
    return query;
}

std::string FileReader::removeQuery(const std::string &path) {
    return findBetween(path, "", "?");
}
//11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
