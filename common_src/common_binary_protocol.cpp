#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <sstream>

#include "common_binary_protocol.h"

std::map<std::string, uint8_t> wpn_map {
    {"none", 0x00},
    {"glock", 0x01},
    {"ak-47", 0x02},
    {"m3", 0x03},
    {"awp", 0x04}
};

std::map<std::string, uint8_t> wpn_t_map {
    {"primary", 0x01},
    {"secondary", 0x02}
};

std::string BinaryProtocol::srlz_buy(std::string &cmd) {
    std::string srlzd_cmd;

    std::vector<std::string> tknzd_cmd;
    tknzd_cmd = tknz(cmd);

    std::string wpn = tknzd_cmd[1];
    uint8_t srlzd_wpn = wpn_map[wpn];

    srlzd_cmd.push_back(0x02);
    srlzd_cmd.push_back(srlzd_wpn);

    return srlzd_cmd;
}


std::string BinaryProtocol::srlz_ammo(std::string &cmd) {
    std::string srlzd_cmd;

    std::vector<std::string> tknzd_cmd;
    tknzd_cmd = tknz(cmd);

    std::string wpn_t = tknzd_cmd[1];
    std::string ammo = tknzd_cmd[2];

    uint8_t srlzd_wpn_t = wpn_t_map[wpn_t];
    uint16_t srlzd_ammo = std::stoi(ammo);

    srlzd_cmd.push_back(0x03);
    srlzd_cmd.push_back(srlzd_wpn_t);
    srlzd_cmd.push_back(srlzd_ammo);

    return srlzd_cmd;
}

std::string BinaryProtocol::srlz(std::string &cmd) {
    std::string srlzd_cmd;

    if (cmd.find("buy ") == 0) {
        srlzd_cmd = srlz_buy(cmd);
    } else if (cmd.find("ammo ") == 0) {
        srlzd_cmd = srlz_ammo(cmd);
    }

    return srlzd_cmd;
}
