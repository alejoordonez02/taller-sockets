#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "common_src/common_socket.h"

#include <string>
#include <cstring>
#include <memory>

class Protocol {
protected:
    const char *hostname;
    const char *servname;
    Socket skt;

public:
    Protocol(const char *&servname, Socket skt);
    Protocol(const char *&hostname, const char *&servname, Socket skt);

    static std::unique_ptr<Protocol> create(
        const char *&hostname,
        const char *&servname,
        const std::string &username);

    static std::unique_ptr<Protocol> create(
        const char *&servname);

    virtual int send(const std::string &msg) = 0;
    virtual int recv(const char *buf) = 0;
    virtual int send_protocol_type() = 0;
    virtual ~Protocol() = default;
};

#endif
