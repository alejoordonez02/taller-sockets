#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCOL_H

#include "common_protocol.h"
#include "common_src/common_socket.h"

#include <string>
#include <memory>

class TextProtocol : public Protocol {
protected:
    const std::string hostname;
    const std::string servname;
    Socket skt;
    
public:
    TextProtocol(const char *&servname, Socket skt);
    TextProtocol(const char *&hostname, const char *&servname, Socket skt);
    int send(const std::string &msg) override;
    int recv(const char *buf) override;
    int send_protocol_type() override;
};

#endif
