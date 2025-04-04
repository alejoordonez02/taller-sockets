#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include <string>
#include <vector>

#include "common_protocol.h"

class BinaryProtocol : public Protocol {
private:
int srlz_cmd_buy(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd);
int srlz_cmd_ammo(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd);
int srlz_cmd_equipment(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd);
int dsrlz_cmd_buy(
    Command &cmd,
    const char*srlzd_cmd);
int dsrlz_cmd_ammo(
    Command &cmd,
    const char*srlzd_cmd);
int dsrlz_cmd_equipment(
    Command &cmd,
    const char*srlzd_cmd);
public:
    int srlz_cmd(
        std::vector<uint8_t> &srlzd_cmd,
        const Command &cmd) override;

    int dsrlz_cmd(
        Command &cmd,
        const char*srlzd_cmd) override;
};

#endif
