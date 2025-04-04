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

std::map<WeaponName, uint8_t> wpn_srl = {
    {WeaponName::GLOCK, 0x01},
    {WeaponName::AK47, 0x02},
    {WeaponName::M3, 0x03},
    {WeaponName::AWP, 0x04}
};

std::map<uint8_t, WeaponName> srl_wpn = {
    {0x01, WeaponName::GLOCK},
    {0x02, WeaponName::AK47},
    {0x03, WeaponName::M3},
    {0x04, WeaponName::AWP}
};

std::map<WeaponType, uint8_t> wpn_t_srl = {
    {WeaponType::PRIMARY, 0x01},
    {WeaponType::SECONDARY, 0x02}
};

std::map<uint8_t, WeaponType> srl_wpn_t = {
    {0x01, WeaponType::PRIMARY},
    {0x02, WeaponType::SECONDARY}
};

int BinaryProtocol::srlz_cmd_buy(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    uint8_t srlzd_wpn = wpn_srl[cmd.get_wpn()];
    srlzd_cmd.push_back(srlzd_wpn);

    return 0;
}

int BinaryProtocol::srlz_cmd_ammo(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    uint8_t srlzd_wpn_t = wpn_t_srl[cmd.get_wpn_t()];
    srlzd_cmd.push_back(srlzd_wpn_t);

    uint16_t count = static_cast<uint16_t>(cmd.get_count());
    count = htons(count);

    uint8_t *srlzd_count = reinterpret_cast<uint8_t *>(&count);

    srlzd_cmd.push_back(srlzd_count[0]);
    srlzd_cmd.push_back(srlzd_count[1]);

    return 0;
}

int BinaryProtocol::srlz_cmd_equipment(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {
// Command::Command(
//     int money,
//     bool knife,
//     WeaponName primary,
//     WeaponName secondary,
//     int primary_ammo,
//     int secondary_ammo) :
//     money(money),
//     knife(knife),
//     primary(primary),
//     secondary(secondary),
//     primary_ammo(primary_ammo),
//     secondary_ammo(secondary_ammo) {}
    // case Type::EQUIPMENT:
    //     srlzd
    return 0;
}

int BinaryProtocol::srlz_cmd(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    uint8_t srlzd_cmd_t = cmd_t_srl[cmd.get_t()];
    srlzd_cmd.push_back(srlzd_cmd_t);

    int ret;

    switch(cmd.get_t()) {
    case Type::BUY:
        ret = srlz_cmd_buy(srlzd_cmd, cmd);
        break;

    case Type::AMMO:
        ret = srlz_cmd_ammo(srlzd_cmd, cmd);
        break;

    case Type::EQUIPMENT:
        ret = srlz_cmd_equipment(srlzd_cmd, cmd);
        break;

    default:
        ret = -1;
    }

    return ret;
}

int BinaryProtocol::dsrlz_cmd_buy(
    Command &cmd,
    const char *srlzd_cmd) {

    Type cmd_t = srl_cmd_t[srlzd_cmd[0]]; // esto lo estoy haciendo dos veces...

    WeaponName wpn = srl_wpn[srlzd_cmd[1]];

    cmd = Command(cmd_t, wpn);

    return 0;
}

int BinaryProtocol::dsrlz_cmd_ammo(
    Command &cmd,
    const char *srlzd_cmd) {

    Type cmd_t = srl_cmd_t[srlzd_cmd[0]];

    WeaponType wpn_t = srl_wpn_t[srlzd_cmd[1]];

    const uint16_t *srlzd_count = reinterpret_cast<const uint16_t*>(&srlzd_cmd[2]);
    int count = (int) ntohs(*srlzd_count);

    cmd = Command(cmd_t, wpn_t, count);

    return 0;
}

int BinaryProtocol::dsrlz_cmd_equipment(
    Command &cmd,
    const char *srlzd_cmd) {

    return 0;
}

int BinaryProtocol::dsrlz_cmd(
    Command &cmd,
    const char *srlzd_cmd) {

    Type cmd_t = srl_cmd_t[srlzd_cmd[0]];

    int ret;

    switch(cmd_t) {
    case Type::BUY:
        ret = dsrlz_cmd_buy(cmd, srlzd_cmd);
        break;

    case Type::AMMO:
        ret = dsrlz_cmd_ammo(cmd, srlzd_cmd);
        break;

    case Type::EQUIPMENT:
        ret = dsrlz_cmd_equipment(cmd, srlzd_cmd);

    default:
        ret = -1;
    }

    return ret;
}
