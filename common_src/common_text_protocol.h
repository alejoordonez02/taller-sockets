#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCOL_H

#include "common_protocol.h"
#include "common_socket.h"

class TextProtocol : public Protocol {
private:
    const Socket skt;
public:
    TextProtocol(Socket&& skt);

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
