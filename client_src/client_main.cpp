#include "common_src/common_socket.h"
#include "common_protocol.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>

#define MAX_BUF 100

int main(int argc, char* argv[]) {

    if (argc != 4)
        return -1;

    const char *hostname = argv[1];
    const char *servname = argv[2];
    std::string username = argv[3];

    auto protocol = Protocol::create(hostname, servname, username);

    while (true) {
        std::string input;
        getline(std::cin, input);

        std::stringstream ss;
        ss.str(input);

        std::string c;

        std::vector<std::string> cmd;

        while (getline(ss, c, ' ')) {
            cmd.push_back(c);
        }

        if (cmd[0] == "exit")
            return 0;


        protocol->send(input);
        char buf[MAX_BUF] = {0};
        protocol->recv(buf);
    }

    return 0;
}
