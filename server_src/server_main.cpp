#include "common_player.h"
#include "common_src/common_socket.h"
#include "common_protocol.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cstdint>

#define BINARY "binary"
#define TEXT "text"

std::string hex_to_string(const std::string &hex) {
    std::string string;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char chr = static_cast<char>(std::stoi(byteString, nullptr, 16));
        string += chr;
    }
    return string;
}

int main(int argc, char* argv[]) {
    if (argc != 3)
        return -1;

    const char *servname = argv[1];
    const char *protocol_type = argv[2];

    Socket skt(servname);
    Socket peer = skt.accept();

    std::unique_ptr<Protocol> protocol;
    if (strcmp(protocol_type, BINARY) == 0) {
        protocol = std::make_unique<BinaryProtocol>(servname, std::move(peer));
    }
    else if (strcmp(protocol_type, TEXT) == 0) {
        protocol = std::make_unique<TextProtocol>(servname, std::move(peer));
    }
    else {
        return -1;
    }

    char *username;
    protocol->recv(username);

    std::cout << username << " has joined!\n";

    protocol->send_protocol_type();

    char buf[512];
    int sz = peer.recvsome(buf, sizeof(buf));

    std::string username(buf + 6, sz - 7);
    username = hex_to_string(username);


    peer.sendall("0607", 4);

    // while (true) {
        
    // }

    return 0;
}
