#include "common_binary_protocol.h"
#include "common_src/common_socket.h"

#include <iostream>
#include <string>
#include <map>
#include <memory>

#define BINARY "binary"
#define TEXT "text"
#define MAX_BUF 100

std::unordered_map<uint8_t, std::string> cmd_map = {
    {0x01, "username"},
    {0x02, "buy"},
    {0x03, "ammo"},
    {0x06, "protocol"},
    {0x07, "equipment"}
};

BinaryProtocol::BinaryProtocol(const char *&servname, Socket skt)
    : Protocol(servname, std::move(skt)), servname(servname), skt(std::move(skt)) {}

BinaryProtocol::BinaryProtocol(const char *&hostname, const char *&servname, Socket skt)
    : Protocol(servname, std::move(skt)), hostname(hostname), servname(servname), skt(std::move(skt)) {}

int BinaryProtocol::send(const std::string &msg) {
    std::cout << "send!\n";
    return 0;
}

int BinaryProtocol::recv(const char *buf) {
    char cmd[MAX_BUF];
    skt.recvsome(cmd);
    std::string opcode(cmd, 2);
    std::string opcmd;
    opcmd = cmd_map[opcode];
    if (strcmp(opcmd, "buy") == 0)
    return 0;
}

int BinaryProtocol::send_protocol_type() {
    std::string msg = "0608";
    return skt.sendall(msg.c_str(), sizeof(msg));
}
