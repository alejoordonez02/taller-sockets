#include "common_binary_serializer.h"

#include <cstdint>
#include <map>
#include <vector>

#include <arpa/inet.h>

#include "common_command.h"
#include "common_output.h"
#include "common_weapon_names.h"

#define SRL_BUY 0x02
#define SRL_AMMO 0x03

#define SRL_EQUIPMENT 0x07

#define SRL_NONE 0x00
#define SRL_GLOCK 0x01
#define SRL_AK47 0x02
#define SRL_M3 0x03
#define SRL_AWP 0x04

#define SRL_PRIMARY 0x01
#define SRL_SECONDARY 0x02

/*
 * Mapeo inverso
 * */
template <typename K, typename V>
std::map<V, K> get_inverse_map(const std::map<K, V>& map) {
    std::map<V, K> inverse_map;
    for (const auto& [key, value]: map) {
        inverse_map[value] = key;
    }

    return inverse_map;
}

/*
 * Consturctor helpers
 * */
void BinarySerializer::initialize_cmd_type_maps() {
    cmd_type_to_srl = {{CommandType::BUY, SRL_BUY}, {CommandType::AMMO, SRL_AMMO}};

    srl_to_cmd_type = get_inverse_map(cmd_type_to_srl);
}

void BinarySerializer::initialize_output_type_maps() {
    output_type_to_srl = {{OutputType::EQUIPMENT, SRL_EQUIPMENT}};

    srl_to_output_type = get_inverse_map(output_type_to_srl);
}

void BinarySerializer::initialize_weapon_name_maps() {
    weapon_name_to_srl = {{WeaponName::NONE, SRL_NONE},
                          {WeaponName::GLOCK, SRL_GLOCK},
                          {WeaponName::AK47, SRL_AK47},
                          {WeaponName::M3, SRL_M3},
                          {WeaponName::AWP, SRL_AWP}};

    srl_to_weapon_name = get_inverse_map(weapon_name_to_srl);
}

void BinarySerializer::initialize_weapon_type_maps() {
    weapon_type_to_srl = {{WeaponType::PRIMARY, SRL_PRIMARY},
                          {WeaponType::SECONDARY, SRL_SECONDARY}};

    srl_to_weapon_type = get_inverse_map(weapon_type_to_srl);
}

/*
 * Constructor
 * */
BinarySerializer::BinarySerializer() {
    initialize_cmd_type_maps();
    initialize_output_type_maps();
    initialize_weapon_name_maps();
    initialize_weapon_type_maps();
}

/*
 * Numbers
 * */
int BinarySerializer::serialize_number(std::vector<uint8_t>& srlzd, const int& n) const {
    uint16_t tmp_n = static_cast<uint16_t>(n);
    tmp_n = htons(tmp_n);

    std::vector<uint8_t> srlzd_n(reinterpret_cast<uint8_t*>(&tmp_n),
                                 reinterpret_cast<uint8_t*>(&tmp_n) + sizeof(tmp_n));

    srlzd.insert(srlzd.end(), srlzd_n.begin(), srlzd_n.end());

    return 0;
}

/*
 * Weapon
 * */
int BinarySerializer::serialize_weapon_name(std::vector<uint8_t>& srlzd,
                                            const WeaponName& weapon) const {
    uint8_t srlzd_weapon = weapon_name_to_srl.at(weapon);
    srlzd.push_back(srlzd_weapon);

    return 0;
}

/*
 * Commands
 * */
int BinarySerializer::serialize_buy(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {
    int ret;

    WeaponName weapon_name = cmd.get_weapon_name();
    ret = serialize_weapon_name(srlzd_cmd, weapon_name);

    return ret;
}

int BinarySerializer::serialize_ammo(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {
    int ret;

    WeaponType weapon_type = cmd.get_weapon_type();
    uint8_t srlzd_weapon_type = weapon_type_to_srl.at(weapon_type);

    int count = cmd.get_count();

    srlzd_cmd.push_back(srlzd_weapon_type);
    ret = serialize_number(srlzd_cmd, count);

    return ret;
}

int BinarySerializer::serialize(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {
    int ret;

    srlzd_cmd.clear();

    CommandType cmd_type = cmd.get_type();

    uint8_t srlzd_cmd_type = cmd_type_to_srl.at(cmd_type);
    srlzd_cmd.push_back(srlzd_cmd_type);

    switch (cmd_type) {
        case CommandType::BUY:
            ret = serialize_buy(srlzd_cmd, cmd);
            break;
        case CommandType::AMMO:
            ret = serialize_ammo(srlzd_cmd, cmd);
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}

int BinarySerializer::deserialize(Command& dsrlzd_cmd,
                                  const std::vector<uint8_t>& srlzd_cmd) const {

    return 0;
}

/*
 * Outputs
 * */
int BinarySerializer::serialize_equipment(std::vector<uint8_t>& srlzd_output,
                                          const Output& output) const {
    int ret;

    int money = output.get_money();
    ret = serialize_number(srlzd_output, money);

    uint8_t knife = output.get_knife();
    srlzd_output.push_back(knife);

    WeaponName primary = output.get_primary();
    ret = serialize_weapon_name(srlzd_output, primary);

    int primary_ammo = output.get_primary_ammo();
    ret = serialize_number(srlzd_output, primary_ammo);

    WeaponName secondary = output.get_secondary();
    ret = serialize_weapon_name(srlzd_output, secondary);

    int secondary_ammo = output.get_secondary_ammo();
    ret = serialize_number(srlzd_output, secondary_ammo);
}

int BinarySerializer::serialize(std::vector<uint8_t>& srlzd_output, const Output& output) const {
    int ret;

    srlzd_output.clear();

    OutputType output_type = output.get_type();

    uint8_t srlzd_output_type = output_type_to_srl.at(output_type);
    srlzd_output.push_back(srlzd_output_type);

    switch (output_type) {
        case OutputType::EQUIPMENT:
            ret = serialize_equipment(srlzd_output, output);
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}

int BinarySerializer::deserialize(Output& dsrlzd_output,
                                  const std::vector<uint8_t>& srlzd_output) const {

    return 0;
}
