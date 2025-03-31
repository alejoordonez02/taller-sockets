#include "common_protocol.h"
#include "common_src/common_socket.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#define MAX_BUF 100
#define BINARY "binary"
#define TEXT "text"

std::string stringToHex(const std::string& text) {
    std::stringstream ss;

    for (char c : text) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)c;
    }

    return ss.str();
}

Protocol::Protocol(const char *&servname, Socket skt)
    : servname(servname), skt(std::move(skt)) {}

Protocol::Protocol(
    const char *&hostname,
    const char *&servname,
    Socket skt)
    : hostname(hostname), servname(servname), skt(std::move(skt)) {}

std::unique_ptr<Protocol> Protocol::create(const char *&servname) {
    return nullptr;
}

std::unique_ptr<Protocol> Protocol::create(
    const char *&hostname,
    const char *&servname,
    const std::string &username) {

    Socket srv(hostname, servname);
    srv.sendall(("010005" + stringToHex(username)).c_str(), sizeof(username));

    char buf[MAX_BUF];
    srv.recvsome(buf, sizeof(buf));

    if (strcmp(buf, "binary"))
        return std::make_unique<BinaryProtocol>(hostname, servname, std::move(srv));
    else if (strcmp(buf,"text"))
        return std::make_unique<TextProtocol>(hostname, servname, std::move(srv));

    return nullptr;
}
