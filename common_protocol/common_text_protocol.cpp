#include "common_text_protocol.h"
#include "common_src/common_socket.h"

#include <iostream>
#include <string>
#include <memory>

TextProtocol::TextProtocol(const char *&servname, Socket skt)
    : Protocol(servname, std::move(skt)), servname(servname), skt(std::move(skt)) {}

TextProtocol::TextProtocol(const char *&hostname, const char *&servname, Socket skt)
    : Protocol(servname, std::move(skt)), hostname(hostname), servname(servname), skt(std::move(skt)) {}

int TextProtocol::send(const std::string &msg) {
    std::cout << "send!\n";
    return 0;
}

int TextProtocol::recv(const char *buf) {
    std::cout << "receive!\n";
    return 0;
}

int TextProtocol::send_protocol_type() {
    std::string msg = "0608";
    return skt.sendall(msg.c_str(), sizeof(msg));
}
