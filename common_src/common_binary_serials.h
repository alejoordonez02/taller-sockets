#ifndef BINARY_SERIALS_H
#define BINARY_SERIALS_H

#include <cstdint>
#include <map>

#include <sys/types.h>

#include "common_command.h"
#include "common_map_inverter.h"
#include "common_output.h"
#include "common_weapon_names.h"

/*
 * Constants
 * */
namespace BinaryConstant {
/*
 * Commands
 * */
constexpr uint8_t SRL_BUY = 0x02;
constexpr uint8_t SRL_AMMO = 0x03;

/*
 * Outputs
 * */
constexpr uint8_t SRL_EQUIPMENT = 0x07;

/*
 * Equipment values
 * */
constexpr uint8_t SRL_NONE = 0x00;
constexpr uint8_t SRL_GLOCK = 0x01;
constexpr uint8_t SRL_AK47 = 0x02;
constexpr uint8_t SRL_M3 = 0x03;
constexpr uint8_t SRL_AWP = 0x04;

/*
 * Weapon types
 * */
constexpr uint8_t SRL_PRIMARY = 0x01;
constexpr uint8_t SRL_SECONDARY = 0x02;

/*
 * Translation maps
 * */
inline const std::map<CommandType, uint8_t> CMD_TYPE_TO_SRL = {{CommandType::BUY, SRL_BUY},
                                                               {CommandType::AMMO, SRL_AMMO}};

inline const std::map<uint8_t, CommandType> SRL_TO_CMD_TYPE =
        MapInverter::get_inverse_map(CMD_TYPE_TO_SRL);

inline const std::map<OutputType, uint8_t> OUTPUT_TYPE_TO_SRL = {
        {OutputType::EQUIPMENT, SRL_EQUIPMENT}};

inline const std::map<uint8_t, OutputType> SRL_TO_OUTPUT_TYPE =
        MapInverter::get_inverse_map(OUTPUT_TYPE_TO_SRL);

inline const std::map<WeaponName, uint8_t> WEAPON_NAME_TO_SRL = {{WeaponName::NONE, SRL_NONE},
                                                                 {WeaponName::GLOCK, SRL_GLOCK},
                                                                 {WeaponName::AK47, SRL_AK47},
                                                                 {WeaponName::M3, SRL_M3},
                                                                 {WeaponName::AWP, SRL_AWP}};

inline const std::map<uint8_t, WeaponName> SRL_TO_WEAPON_NAME =
        MapInverter::get_inverse_map(WEAPON_NAME_TO_SRL);

inline const std::map<WeaponType, uint8_t> WEAPON_TYPE_TO_SRL = {
        {WeaponType::PRIMARY, SRL_PRIMARY}, {WeaponType::SECONDARY, SRL_SECONDARY}};

inline const std::map<uint8_t, WeaponType> SRL_TO_WEAPON_TYPE =
        MapInverter::get_inverse_map(WEAPON_TYPE_TO_SRL);
}  // namespace BinaryConstant

#endif
