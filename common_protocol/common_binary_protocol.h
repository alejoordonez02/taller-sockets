#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include "common_protocol.h"
#include "common_src/common_socket.h"

#include <string>
#include <memory>

class BinaryProtocol : public Protocol {
protected:
    const char *hostname;
    const char *servname;
    Socket skt;

public:
    BinaryProtocol(const char *&servname, Socket skt);
    BinaryProtocol(const char *&hostname, const char *&servname, Socket skt);
    int send(const std::string &msg) override;
    int recv(const char *buf) override;
    int send_protocol_type() override;
};

#endif
