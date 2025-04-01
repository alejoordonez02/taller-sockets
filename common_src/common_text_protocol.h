#ifndef TEXT_PROTOCOL_H
#define TEXT_PROTOCOL_H

#include "common_protocol.h"

class TextProtocol : public Protocol {
public:
    int srlz_cmd(
        std::vector<uint8_t> &srlzd_cmd,
        const Command &cmd) override;

    int dsrlz_cmd(
        Command &cmd,
        std::vector<uint8_t> &srlzd_cmd) override;
};

#endif
