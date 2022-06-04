// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 80

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "HTTP/1.0 200 OK\n"
                  "Content-Type: text/html; charset=UTF-8\n"
                  "Connection: close\n"
                  "Content-Length: 21\n"
                  "\n"
                  "<h1>Test page...</h1>";
    char *html = "HTTP/1.0 200 OK\n"
                 "Age: 289005\n"
                 "Cache-Control: max-age=604800\n"
                 "Content-Type: text/html; charset=UTF-8\n"
                 "Date: Wed, 11 May 2022 11:11:49 GMT\n"
                 "Etag: \"3147526947+ident\"\n"
                 "Expires: Wed, 18 May 2022 11:11:49 GMT\n"
                 "Last-Modified: Thu, 17 Oct 2019 07:18:26 GMT\n"
                 "Server: ECS (nyb/1D20)\n"
                 "Vary: Accept-Encoding\n"
                 "X-Cache: HIT\n"
                 "Content-Length: 1256\n"
                 "Connection: close\n"
                 "\n"
                 "<!doctype html>\n"
                 "<html>\n"
                 "<head>\n"
                 "    <title>Example Domain</title>\n"
                 "\n"
                 "    <meta charset=\"utf-8\" />\n"
                 "    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />\n"
                 "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n"
                 "    <style type=\"text/css\">\n"
                 "    body {\n"
                 "        background-color: #f0f0f2;\n"
                 "        margin: 0;\n"
                 "        padding: 0;\n"
                 "        font-family: -apple-system, system-ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;\n"
                 "        \n"
                 "    }\n"
                 "    div {\n"
                 "        width: 600px;\n"
                 "        margin: 5em auto;\n"
                 "        padding: 2em;\n"
                 "        background-color: #fdfdff;\n"
                 "        border-radius: 0.5em;\n"
                 "        box-sh\n"
                 "adow: 2px 3px 7px 2px rgba(0,0,0,0.02);\n"
                 "    }\n"
                 "    a:link, a:visited {\n"
                 "        color: #38488f;\n"
                 "        text-decoration: none;\n"
                 "    }\n"
                 "    @media (max-width: 700px) {\n"
                 "        div {\n"
                 "            margin: 0 auto;\n"
                 "            width: auto;\n"
                 "        }\n"
                 "    }\n"
                 "    </style>    \n"
                 "</head>\n"
                 "\n"
                 "<body>\n"
                 "<div>\n"
                 "    <h1>Example Domain</h1>\n"
                 "    <p>This domain is for use in illustrative examples in documents. You may use this\n"
                 "    domain in literature without prior coordination or asking for permission.</p>\n"
                 "    <p><a href=\"https://www.iana.org/domains/example\">More information...</a></p>\n"
                 "</div>\n"
                 "</body>\n"
                 "</html>\n"
                 "cale=1\" />\n"
                 "    <style type=\"text/css\">\n"
                 "    body {\n"
                 "        background-color: #f0f0f2;\n"
                 "        margin: 0;\n"
                 "        padding: 0;\n"
                 "        font-family: -apple-system, system-ui, BlinkMacSystemFont, \"Segoe UI\", \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;\n"
                 "        \n"
                 "    }\n"
                 "    div {\n"
                 "        width: 600px;\n"
                 "        margin: 5em auto;\n"
                 "        padding: 2em;\n"
                 "        background-color: #fdfdff;\n"
                 "        border-radius: 0.5em;\n"
                 "        box-sh";

    int size = strlen(html);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR /*| SO_REUSEPORT*/, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    //send(new_socket, hello, strlen(hello), 0);
    send(new_socket, html, strlen(html), 0);
    printf("Hello message sent\n");
    return 0;
}
