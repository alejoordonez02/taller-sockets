#include "common_protocol.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <arpa/inet.h>

std::unique_ptr<Protocol> Protocol::create(const ProtocolType &prtcl_t) {
    if (prtcl_t == ProtocolType::BINARY)
        return std::make_unique<BinaryProtocol>();
    else if (prtcl_t == ProtocolType::TEXT)
        return std::make_unique<TextProtocol>();

    return nullptr;
}

int Protocol::srlz_username(
    std::vector<uint8_t> &srlzd_username,
    const std::string &username) {

    srlzd_username.clear();

    uint16_t len = static_cast<uint16_t>(username.size());
    len = htons(len);
    uint8_t *len_ptr = reinterpret_cast<uint8_t *>(&len);

    srlzd_username.push_back(0x01);
    srlzd_username.insert(
        srlzd_username.end(), len_ptr, len_ptr + sizeof(uint16_t));
    srlzd_username.insert(
        srlzd_username.end(), username.begin(), username.end());

    return 0;
}

int Protocol::srlz_prtcl_t(
    std::vector<uint8_t> &srlzd_prtcl_t,
    const std::string &prtcl_t) {

    if (prtcl_t == "binary")
        srlzd_prtcl_t = {0x06, 0x07};
    else if (prtcl_t == "text")
        srlzd_prtcl_t = {0x06, 0x08};
    else
        return -1;

    return 0;
}

int Protocol::dsrlz_prtcl_t(
    ProtocolType *prtcl_t,
    const char *srlzd_prtcl_t) {

    if (srlzd_prtcl_t[0] != 0x06)
        return -1;

    if (srlzd_prtcl_t[1] == 0x07)
        *prtcl_t = ProtocolType::BINARY;
    else if (srlzd_prtcl_t[1] == 0x08)
        *prtcl_t = ProtocolType::TEXT;
    else
        return -1;

    return 0;
}

int Protocol::dsrlz_username(
    std::string &username,
    const char *srlzd_username) {

    const uint16_t *srlzd_len = reinterpret_cast<const uint16_t *>(srlzd_username + 1);
    uint16_t len = ntohs(*srlzd_len);

    username = std::string (srlzd_username + 3, len);

    return 0;
}
