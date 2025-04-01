#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <map>
#include <arpa/inet.h>

#include "common_binary_protocol.h"
#include "common_command.h"

std::map<Type, uint8_t> cmd_t_srl = {
    {Type::BUY, 0x02},
    {Type::AMMO, 0x03}
};

std::map<uint8_t, Type> srl_cmd_t = {
    {0x02, Type::BUY},
    {0x03, Type::AMMO}
};

std::map<Weapon, uint8_t> wpn_srl = {
    {Weapon::GLOCK, 0x01},
    {Weapon::AK47, 0x02},
    {Weapon::M3, 0x03},
    {Weapon::AWP, 0x04}
};

std::map<uint8_t, Weapon> srl_wpn = {
    {0x01, Weapon::GLOCK},
    {0x02, Weapon::AK47},
    {0x03, Weapon::M3},
    {0x04, Weapon::AWP}
};

std::map<WeaponType, uint8_t> wpn_t_srl = {
    {WeaponType::PRIMARY, 0x01},
    {WeaponType::SECONDARY, 0x02}
};

std::map<uint8_t, WeaponType> srl_wpn_t = {
    {0x01, WeaponType::PRIMARY},
    {0x02, WeaponType::SECONDARY}
};

int BinaryProtocol::srlz_cmd(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    uint8_t srlzd_cmd_t = cmd_t_srl[cmd.get_t()];
    srlzd_cmd.push_back(srlzd_cmd_t);

    uint8_t srlzd_wpn;
    uint8_t srlzd_wpn_t;
    uint16_t count;
    uint8_t *srlzd_count;

    switch(cmd.get_t()) {
    case Type::BUY:
        srlzd_wpn = wpn_srl[cmd.get_wpn()];
        srlzd_cmd.push_back(srlzd_wpn);
        break;

    case Type::AMMO:
        srlzd_wpn_t = wpn_t_srl[cmd.get_wpn_t()];
        srlzd_cmd.push_back(srlzd_wpn_t);

        count = static_cast<uint16_t>(cmd.get_count());
        count = htons(count);
        srlzd_count = reinterpret_cast<uint8_t *>(&count);
        srlzd_cmd.push_back(srlzd_count[0]);
        srlzd_cmd.push_back(srlzd_count[1]);
        break;

    default:
        return -1;
    }

    return 0;
}

int BinaryProtocol::dsrlz_cmd(
    Command &cmd,
    std::vector<uint8_t> &srlzd_cmd) {

    Type cmd_t = srl_cmd_t[srlzd_cmd[0]];
    Weapon wpn;
    WeaponType wpn_t;
    uint16_t *srlzd_count;
    int count;

    switch(cmd_t) {
    case Type::BUY:
        wpn = srl_wpn[srlzd_cmd[1]];
        cmd = Command(cmd_t, wpn);
        break;

    case Type::AMMO:
        wpn_t = srl_wpn_t[srlzd_cmd[1]];
        srlzd_count = reinterpret_cast<uint16_t*>(&srlzd_cmd[2]);
        count = (int) ntohs(*srlzd_count);
        cmd = Command(cmd_t, wpn_t, count);
        break;

    default:
        return -1;
    }

    return 0;
}
