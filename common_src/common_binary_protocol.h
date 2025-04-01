#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include <string>
#include <vector>

#include "common_protocol.h"

class BinaryProtocol : public Protocol {
public:
    int srlz_cmd(
        std::vector<uint8_t> &srlzd_cmd,
        const Command &cmd) override;

    int dsrlz_cmd(
        Command &cmd,
        std::vector<uint8_t> &srlzd_cmd) override;
};

#endif
