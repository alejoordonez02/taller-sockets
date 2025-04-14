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
    uint8_t srlzd_weapon = BinaryConstant::WEAPON_NAME_TO_SRL.at(weapon);
    srlzd.push_back(srlzd_weapon);
}

/*
 * Commands
 * */
CommandType BinarySerializer::get_deserialized_command_type(
        const std::vector<uint8_t>& srlzd_cmd) const {
    return BinaryConstant::SRL_TO_CMD_TYPE.at(srlzd_cmd[0]);
}

void BinarySerializer::serialize_buy(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {

    WeaponName weapon_name = cmd.get_weapon_name();
    serialize_weapon_name(srlzd_cmd, weapon_name);
}

void BinarySerializer::serialize_ammo(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const {
    WeaponType weapon_type = cmd.get_weapon_type();
    uint8_t srlzd_weapon_type = BinaryConstant::WEAPON_TYPE_TO_SRL.at(weapon_type);

    int count = cmd.get_count();

    srlzd_cmd.push_back(srlzd_weapon_type);
    serialize_number(srlzd_cmd, count);
}

std::vector<uint8_t> BinarySerializer::serialize(const Command& cmd) const {
    std::vector<uint8_t> srlzd_cmd;

    CommandType cmd_type = cmd.get_type();

    uint8_t srlzd_cmd_type = BinaryConstant::CMD_TYPE_TO_SRL.at(cmd_type);
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
    WeaponName weapon_name = BinaryConstant::SRL_TO_WEAPON_NAME.at(srlzd_cmd[1]);

    Command dsrlzd_cmd(CommandType::BUY, weapon_name);

    return dsrlzd_cmd;
}

Command BinarySerializer::deserialize_ammo(const std::vector<uint8_t>& srlzd_cmd) const {
    WeaponType weapon_type = BinaryConstant::SRL_TO_WEAPON_TYPE.at(srlzd_cmd[1]);
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
    return BinaryConstant::SRL_TO_OUTPUT_TYPE.at(srlzd_output[0]);
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

    uint8_t srlzd_output_type = BinaryConstant::OUTPUT_TYPE_TO_SRL.at(output_type);
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

    const WeaponName primary = BinaryConstant::SRL_TO_WEAPON_NAME.at(srlzd_output[4]);
    const int primary_ammo = get_deserialized_number(srlzd_output[5]);

    const WeaponName secondary = BinaryConstant::SRL_TO_WEAPON_NAME.at(srlzd_output[7]);
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
