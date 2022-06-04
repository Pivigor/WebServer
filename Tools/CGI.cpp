#include "CGI.hpp"

extern char **environ;

std::string CGI::executeCGI(const std::string& app, const std::string& arg, const std::string& query, const std::string& body) {
    int in_fd[2];
    int out_fd[2];
    pipe(in_fd);
    pipe(out_fd);

    pid_t pid = fork();
    if (pid != 0) {
        // Main process
        close(in_fd[STDIN_FILENO]);
        close(out_fd[STDOUT_FILENO]);
        if (!body.empty()) {
            write(in_fd[STDOUT_FILENO], body.c_str(), body.size() + 1);
        }
        close(in_fd[STDOUT_FILENO]);
        wait(nullptr);
        std::string result = FileReader::readFileDescriptor(out_fd[STDIN_FILENO], 1024);
        close(out_fd[STDIN_FILENO]);
        return result;
    } else {
        // Child process
        dup2(in_fd[STDIN_FILENO], STDIN_FILENO);
        dup2(out_fd[STDOUT_FILENO], STDOUT_FILENO);
        close(in_fd[STDIN_FILENO]);
        close(in_fd[STDOUT_FILENO]);
        close(out_fd[STDIN_FILENO]);
        close(out_fd[STDOUT_FILENO]);
        //environ[3] = "TEST_VAR=123";

        char* args[3] = {
                const_cast<char*>(app.c_str()),   // Application name
                const_cast<char*>(arg.c_str()),  // First arg to application
                nullptr};
        if (arg.empty()) {
            args[1] = nullptr;
        }

        if (!query.empty()) {
            std::string queryStr = "QUERY_STRING=" + query;
            char *envs[2] = {
                    const_cast<char *>(queryStr.c_str()),
                    nullptr};
            environ = appendEnv(envs);
        }

        execvp(args[0], args);
        std::cout << "WebServer: CGI failure" << std::endl;
        exit(0);
    }
}

// Content move semantic
char** CGI::appendEnv(char** envToAppend) {
    size_t size1 = sizeEnv(envToAppend);
    size_t size2 = sizeEnv(environ);

    char** newArgs = new char*[size1 + size2 + 1];
    for (size_t i = 0; i < size1; i++) {
        newArgs[i] = envToAppend[i];
    }
    for (size_t i = 0; i < size2; i++) {
        newArgs[i + size1] = environ[i];
    }
    newArgs[size1 + size2] = nullptr;
    return newArgs;
}

size_t CGI::sizeEnv(char **env) {
    size_t size = 0;
    while (env[size] != nullptr) {
        size++;
    }
    return size;
}
