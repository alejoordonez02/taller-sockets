#include <map>
#include <cstdint>
#include <vector>

#include "common_binary_serializer.h"
#include "common_weapon_names.h"
#include "common_command.h"
#include "common_output.h"

#define SRL_BUY 0x02
#define SRL_AMMO 0x03

#define SRL_EQUIPMENT 0x07

#define SRL_NONE 0x00
#define SRL_GLOCK 0x01
#define SRL_AK47 0x02
#define SRL_M3 0x03
#define SRL_AWP 0x04

/*
 * Mapeo inverso
 * */
template <typename K, typename V>
std::map<V, K> get_inverse_map(const std::map<K, V>& map) {
    std::map<V, K> inverse_map;
    for (const auto& [key, value] : map) {
        inverse_map[value] = key;
    }
    return inverse_map;
}

/*
 * Consturctor helpers
 * */
void BinarySerializer::initialize_cmd_maps() {
    cmd_to_srl = {
        {CommandType::BUY, SRL_BUY},
        {CommandType::AMMO, SRL_AMMO}
    };

    srl_to_cmd = get_inverse_map(cmd_to_srl);
}

void BinarySerializer::initialize_output_maps() {
    output_to_srl = {
        {OutputType::EQUIPMENT, SRL_EQUIPMENT}
    };

    srl_to_output = get_inverse_map(output_to_srl);
}

void BinarySerializer::initialize_weapon_maps() {
    weapon_to_srl = {
        {WeaponName::NONE, SRL_NONE},
        {WeaponName::GLOCK, SRL_GLOCK},
        {WeaponName::AK47, SRL_AK47},
        {WeaponName::M3, SRL_M3},
        {WeaponName::AWP, SRL_AWP}
    };

    srl_to_weapon = get_inverse_map(weapon_to_srl);
}

/*
 * Constructor
 * */
BinarySerializer::BinarySerializer() {
    initialize_cmd_maps();
    initialize_output_maps();
    initialize_weapon_maps();
}

/*
 * Commands
 * */
int BinarySerializer::serialize(
    std::vector<uint8_t>& srlzd_cmd,
    const Command& cmd) const {

    return 0;
}

int BinarySerializer::deserialize(
    Command& dsrlzd_cmd,
    const std::vector<uint8_t>& srlzd_cmd) const {

    return 0;
}

/*
 * Outputs
 * */
int BinarySerializer::serialize(
    std::vector<uint8_t>& srlzd_output,
    const Output& output) const {

    return 0;
}

int BinarySerializer::deserialize(
    Output& dsrlzd_output,
    const std::vector<uint8_t>& srlzd_output) const {

    return 0;
}
