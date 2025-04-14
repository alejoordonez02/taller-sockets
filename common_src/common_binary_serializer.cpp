#include "common_binary_serializer.h"

#include <cstdint>
#include <map>
#include <vector>

#include <arpa/inet.h>

#include "common_binary_serials.h"
#include "common_command.h"
#include "common_output.h"
#include "common_weapon_names.h"

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
    cmd_type_to_srl = {{CommandType::BUY, BinaryConstant::SRL_BUY},
                       {CommandType::AMMO, BinaryConstant::SRL_AMMO}};

    srl_to_cmd_type = get_inverse_map(cmd_type_to_srl);
}

void BinarySerializer::initialize_output_type_maps() {
    output_type_to_srl = {{OutputType::EQUIPMENT, BinaryConstant::SRL_EQUIPMENT}};

    srl_to_output_type = get_inverse_map(output_type_to_srl);
}

void BinarySerializer::initialize_weapon_name_maps() {
    weapon_name_to_srl = {{WeaponName::NONE, BinaryConstant::SRL_NONE},
                          {WeaponName::GLOCK, BinaryConstant::SRL_GLOCK},
                          {WeaponName::AK47, BinaryConstant::SRL_AK47},
                          {WeaponName::M3, BinaryConstant::SRL_M3},
                          {WeaponName::AWP, BinaryConstant::SRL_AWP}};

    srl_to_weapon_name = get_inverse_map(weapon_name_to_srl);
}

void BinarySerializer::initialize_weapon_type_maps() {
    weapon_type_to_srl = {{WeaponType::PRIMARY, BinaryConstant::SRL_PRIMARY},
                          {WeaponType::SECONDARY, BinaryConstant::SRL_SECONDARY}};

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
void BinarySerializer::serialize_number(std::vector<uint8_t>& srlzd, const int& n) const {
    uint16_t tmp_n = static_cast<uint16_t>(n);
    tmp_n = htons(tmp_n);

    std::vector<uint8_t> srlzd_n(reinterpret_cast<uint8_t*>(&tmp_n),
                                 reinterpret_cast<uint8_t*>(&tmp_n) + sizeof(tmp_n));

    srlzd.insert(srlzd.end(), srlzd_n.begin(), srlzd_n.end());
}

int BinarySerializer::get_deserialized_number(const uint8_t& srlzd_n) const {
    const uint16_t* tmp_n = reinterpret_cast<const uint16_t*>(&srlzd_n);
    int n = ntohs(*tmp_n);

    return n;
}

/*
 * Weapon
 * */
void BinarySerializer::serialize_weapon_name(std::vector<uint8_t>& srlzd,
                                             const WeaponName& weapon) const {
    uint8_t srlzd_weapon = weapon_name_to_srl.at(weapon);
    srlzd.push_back(srlzd_weapon);
}

/*
 * Commands
 * */
CommandType BinarySerializer::get_deserialized_command_type(
        const std::vector<uint8_t>& srlzd_cmd) const {
    return srl_to_cmd_type.at(srlzd_cmd[0]);
}

void BinarySerializer::serialize_buy(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {

    WeaponName weapon_name = cmd.get_weapon_name();
    serialize_weapon_name(srlzd_cmd, weapon_name);
}

void BinarySerializer::serialize_ammo(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {
    WeaponType weapon_type = cmd.get_weapon_type();
    uint8_t srlzd_weapon_type = weapon_type_to_srl.at(weapon_type);

    int count = cmd.get_count();

    srlzd_cmd.push_back(srlzd_weapon_type);
    serialize_number(srlzd_cmd, count);
}

std::vector<uint8_t> BinarySerializer::serialize(const Command& cmd) const {
    std::vector<uint8_t> srlzd_cmd;

    CommandType cmd_type = cmd.get_type();

    uint8_t srlzd_cmd_type = cmd_type_to_srl.at(cmd_type);
    srlzd_cmd.push_back(srlzd_cmd_type);

    switch (cmd_type) {
        case CommandType::BUY:
            serialize_buy(srlzd_cmd, cmd);
            break;
        case CommandType::AMMO:
            serialize_ammo(srlzd_cmd, cmd);
            break;
        default:
            srlzd_cmd.clear();
            break;
    }

    return srlzd_cmd;
}

Command BinarySerializer::deserialize_buy(const std::vector<uint8_t>& srlzd_cmd) const {
    WeaponName weapon_name = srl_to_weapon_name.at(srlzd_cmd[1]);

    Command dsrlzd_cmd(CommandType::BUY, weapon_name);

    return dsrlzd_cmd;
}

Command BinarySerializer::deserialize_ammo(const std::vector<uint8_t>& srlzd_cmd) const {
    WeaponType weapon_type = srl_to_weapon_type.at(srlzd_cmd[1]);
    int count = get_deserialized_number(srlzd_cmd[2]);

    Command dsrlzd_cmd(CommandType::AMMO, weapon_type, count);

    return dsrlzd_cmd;
}

Command BinarySerializer::deserialize_command(const std::vector<uint8_t>& srlzd_cmd) const {
    CommandType cmd_type = get_deserialized_command_type(srlzd_cmd);

    switch (cmd_type) {
        case CommandType::BUY:
            return deserialize_buy(srlzd_cmd);
        case CommandType::AMMO:
            return deserialize_ammo(srlzd_cmd);
        default:
            return Command();
    }
}

/*
 * Outputs
 * */
OutputType BinarySerializer::get_deserialized_output_type(
        const std::vector<uint8_t>& srlzd_output) const {
    return srl_to_output_type.at(srlzd_output[0]);
}

void BinarySerializer::serialize_equipment(std::vector<uint8_t>& srlzd_output,
                                           const Output& output) const {
    int money = output.get_money();
    serialize_number(srlzd_output, money);

    uint8_t knife = output.get_knife();
    srlzd_output.push_back(knife);

    WeaponName primary = output.get_primary();
    serialize_weapon_name(srlzd_output, primary);

    int primary_ammo = output.get_primary_ammo();
    serialize_number(srlzd_output, primary_ammo);

    WeaponName secondary = output.get_secondary();
    serialize_weapon_name(srlzd_output, secondary);

    int secondary_ammo = output.get_secondary_ammo();
    serialize_number(srlzd_output, secondary_ammo);
}

std::vector<uint8_t> BinarySerializer::serialize(const Output& output) const {
    std::vector<uint8_t> srlzd_output;

    OutputType output_type = output.get_type();

    uint8_t srlzd_output_type = output_type_to_srl.at(output_type);
    srlzd_output.push_back(srlzd_output_type);

    switch (output_type) {
        case OutputType::EQUIPMENT:
            serialize_equipment(srlzd_output, output);
            break;
        default:
            srlzd_output.clear();
            break;
    }

    return srlzd_output;
}


Output BinarySerializer::deserialize_equipment(const std::vector<uint8_t>& srlzd_output) const {
    const int money = get_deserialized_number(srlzd_output[1]);

    const bool knife = srlzd_output[3];

    const WeaponName primary = srl_to_weapon_name.at(srlzd_output[4]);
    const int primary_ammo = get_deserialized_number(srlzd_output[5]);

    const WeaponName secondary = srl_to_weapon_name.at(srlzd_output[7]);
    const int secondary_ammo = get_deserialized_number(srlzd_output[8]);

    Output dsrlzd_output(OutputType::EQUIPMENT, money, knife, primary, primary_ammo, secondary,
                         secondary_ammo);

    return dsrlzd_output;
}

Output BinarySerializer::deserialize_output(const std::vector<uint8_t>& srlzd_output) const {
    OutputType output_type = get_deserialized_output_type(srlzd_output);

    switch (output_type) {
        case OutputType::EQUIPMENT:
            return deserialize_equipment(srlzd_output);
            break;
        default:
            return Output();
    }
}
