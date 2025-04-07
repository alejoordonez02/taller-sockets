#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include "common_protocol.h"
#include "common_socket.h"

class BinaryProtocol : public Protocol {
private:
    const Socket skt;
public:
    BinaryProtocol(Socket&& skt);

    /*
     * Commands
     * */
    int send(const Command& cmd) const override;
    int recv(Command& cmd) const override;

    /*
     * Outputs
     * */
    int send(const Output& output) const override;
    int recv(Output& output) const override;
};

#endif
