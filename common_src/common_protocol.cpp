#include "common_protocol.h"
#include "common_binary_protocol.h"
#include "common_text_protocol.h"

#include <string>
#include <vector>
#include <cstdint>
#include <arpa/inet.h>
#include <memory>
#include <sstream>

std::vector<std::string> Protocol::tknz(const std::string &cmd) {
    std::vector<std::string> tknzd_cmd;

    std::istringstream cmd_iss(cmd);

    std::string tkn;
    while (cmd_iss >> tkn)
        tknzd_cmd.push_back(tkn);

    return tknzd_cmd;
}


std::unique_ptr<Protocol> Protocol::create(ProtocolType &prtcl_t) {
    if (prtcl_t == ProtocolType::BINARY)
        return std::make_unique<BinaryProtocol>();
    else if (prtcl_t == ProtocolType::TEXT)
        return std::make_unique<TextProtocol>();

    return nullptr;
}

std::string Protocol::srlz_username(const std::string &username) {
    std::string srlzd_username;

    uint16_t len = username.size();
    len = htons(len);

    srlzd_username.push_back(0x01);
    srlzd_username.append(reinterpret_cast<char*>(&len), sizeof(len));
    srlzd_username.append(username);

    return srlzd_username;
}

ProtocolType Protocol::dsrlz_prtcl_t(char &srlzd_prtcl_t) {
    ProtocolType prtcl_t;

    if (srlzd_prtcl_t == 0x07)
        prtcl_t = ProtocolType::BINARY;
    else if (srlzd_prtcl_t == 0x08)
        prtcl_t = ProtocolType::TEXT;

    return prtcl_t;
}

std::string Protocol::dsrlz_username(char *srlzd_username) {
    uint16_t len = (static_cast<unsigned char>(srlzd_username[1]) << 8)
        | static_cast<unsigned char>(srlzd_username[2]);

    std::string username(srlzd_username + 3, len);

    return username;
}

std::string Protocol::srlz_prtcl_t(const std::string &prtcl_t) {
    std::string srlzd_prtcl_t;

    srlzd_prtcl_t.push_back(0x06);

    if (prtcl_t == "binary")
        srlzd_prtcl_t.push_back(0x07);
    else if (prtcl_t == "text")
        srlzd_prtcl_t.push_back(0x08);

    return srlzd_prtcl_t;
}
