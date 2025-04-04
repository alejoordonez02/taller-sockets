#include "common_text_protocol.h"

int TextProtocol::srlz_cmd(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    return 0;
}

int TextProtocol::dsrlz_cmd(
    Command &cmd,
    const char*srlzd_cmd) {

    return 0;
}
