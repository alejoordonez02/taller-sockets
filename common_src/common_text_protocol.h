#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCOL_H

#include <string>

#include "common_protocol.h"
#include "common_text_serializer.h"

class TextProtocol: public Protocol {
private:
    Socket skt;
    TextSerializer srl;

public:
    explicit TextProtocol(Socket&& skt);

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
