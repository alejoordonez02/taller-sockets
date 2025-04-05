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
    {Type::AMMO, 0x03},
    {Type::EQUIPMENT, 0x07}
};

std::map<uint8_t, Type> srl_cmd_t = {
    {0x02, Type::BUY},
    {0x03, Type::AMMO},
    {0x07, Type::EQUIPMENT}
};

std::map<WeaponName, uint8_t> wpn_srl = {
    {WeaponName::NONE, 0x00},
    {WeaponName::GLOCK, 0x01},
    {WeaponName::AK47, 0x02},
    {WeaponName::M3, 0x03},
    {WeaponName::AWP, 0x04}
};

std::map<uint8_t, WeaponName> srl_wpn = {
    {0x00, WeaponName::NONE},
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

// 07 | 01 f4 | 01 | 00 | 00 00 | 01 | 00 1e
int BinaryProtocol::srlz_cmd_equipment(
    std::vector<uint8_t> &srlzd_cmd,
    const Command &cmd) {

    uint16_t money = static_cast<uint16_t>(cmd.get_money());
    money = htons(money);
    uint8_t *srlzd_money = reinterpret_cast<uint8_t *>(&money);

    uint8_t srlzd_knife = cmd.get_knife();

    uint8_t srlzd_primary = wpn_srl[cmd.get_primary()];

    uint8_t srlzd_secondary = wpn_srl[cmd.get_secondary()];

    uint16_t primary_ammo = static_cast<uint16_t>(cmd.get_primary_ammo());
    primary_ammo = htons(primary_ammo);
    uint8_t *srlzd_primary_ammo = reinterpret_cast<uint8_t *>(&primary_ammo);

    uint16_t secondary_ammo = static_cast<uint16_t>(cmd.get_secondary_ammo());
    secondary_ammo = htons(secondary_ammo);
    uint8_t *srlzd_secondary_ammo = reinterpret_cast<uint8_t *>(&secondary_ammo);

    srlzd_cmd.push_back(srlzd_money[0]);
    srlzd_cmd.push_back(srlzd_money[1]);
    srlzd_cmd.push_back(srlzd_knife);
    srlzd_cmd.push_back(srlzd_primary);
    srlzd_cmd.push_back(srlzd_primary_ammo[0]);
    srlzd_cmd.push_back(srlzd_primary_ammo[1]);
    srlzd_cmd.push_back(srlzd_secondary);
    srlzd_cmd.push_back(srlzd_secondary_ammo[0]);
    srlzd_cmd.push_back(srlzd_secondary_ammo[1]);

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

// 0    | 1     | 2   | 3     | 4          | 5       | 6
// cmd_t| money |knife|primary|primary_ammo|secondary|secondary_ammo
// 07   | 01 f4 | 01  | 00    | 00 00      | 01      | 00 1e
int BinaryProtocol::dsrlz_cmd_equipment(
    Command &cmd,
    const char *srlzd_cmd) {

    Type dsrlzd_cmd_t = srl_cmd_t[srlzd_cmd[0]];

    const uint16_t *srlzd_money = reinterpret_cast<const uint16_t*>(&srlzd_cmd[1]);
    int dsrlzd_money = (int) ntohs(*srlzd_money);

    bool dsrlzd_knife = srlzd_cmd[3];

    WeaponName dsrlzd_primary = srl_wpn[srlzd_cmd[4]];

    const uint16_t *srlzd_primary_ammo = reinterpret_cast<const uint16_t*>(&srlzd_cmd[5]);
    int dsrlzd_primary_ammo = (int) ntohs(*srlzd_primary_ammo);

    WeaponName dsrlzd_secondary = srl_wpn[srlzd_cmd[7]];

    const uint16_t *srlzd_secondary_ammo = reinterpret_cast<const uint16_t*>(&srlzd_cmd[8]);
    int dsrlzd_secondary_ammo = (int) ntohs(*srlzd_secondary_ammo);

    Command dsrlzd_cmd(
        dsrlzd_cmd_t,
        dsrlzd_money,
        dsrlzd_knife,
        dsrlzd_primary,
        dsrlzd_secondary,
        dsrlzd_primary_ammo,
        dsrlzd_secondary_ammo);

    cmd = dsrlzd_cmd;

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
        break;

    default:
        ret = -1;
    }

    return ret;
}
