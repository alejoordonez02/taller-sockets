#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include "common_binary_serializer.h"
#include "common_protocol.h"

class BinaryProtocol: public Protocol {
private:
    Socket skt;
    BinarySerializer srl;

public:
    explicit BinaryProtocol(Socket&& skt);

    /*
     * Commands
     * */
    bool send(const Command& cmd) override;
    Command recv_command() override;

    /*
     * Outputs
     * */
    bool send(const Output& output) override;
    Output recv_output() override;
};

#endif
