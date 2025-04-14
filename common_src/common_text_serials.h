#ifndef TEXT_SERIALS_H
#define TEXT_SERIALS_H

#include <map>
#include <string>

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
 * Constants
 * */
namespace TextConstant {
/*
 * Delimiters
 * */
inline const std::string DELIMITERS = ":,\n";
inline const std::string LINE_DELIMITER = "\n";
inline const std::string VALUE_DELIMITER = ":";
inline const std::string AMMO_DELIMITER = ",";

/*
 * Commands
 * */
inline const std::string SRL_BUY = "buy.weapon";
inline const std::string SRL_AMMO_PRIMARY = "buy.ammo.primary";
inline const std::string SRL_AMMO_SECONDARY = "buy.ammo.secondary";

/*
 * Outputs
 * */
inline const std::string SRL_EQUIPMENT = "equipment.money";

/*
 * Equipments
 * */
inline const std::string SRL_MONEY = "equipment.money";
inline const std::string SRL_KNIFE = "equipment.knife";
inline const std::string SRL_PRIMARY = "equipment.primary";
inline const std::string SRL_SECONDARY = "equipment.secondary";

/*
 * Equipment values
 * */
inline const std::string SRL_KNIFE_EQUIPPED = "true";
inline const std::string SRL_KNIFE_NOT_EQUIPPED = "false";
inline const std::string SRL_NONE = "none";
inline const std::string SRL_GLOCK = "glock";
inline const std::string SRL_AK47 = "ak-47";
inline const std::string SRL_M3 = "m3";
inline const std::string SRL_AWP = "awp";

/*
 * Translation maps
 * */
inline const std::map<std::string, CommandType> SRL_TO_CMD_TYPE = {
        {SRL_BUY, CommandType::BUY},
        {SRL_AMMO_PRIMARY, CommandType::AMMO},
        {SRL_AMMO_SECONDARY, CommandType::AMMO}};

inline const std::map<OutputType, std::string> OUTPUT_TYPE_TO_SRL = {
        {OutputType::EQUIPMENT, SRL_EQUIPMENT}};

inline const std::map<std::string, OutputType> SRL_TO_OUTPUT_TYPE =
        get_inverse_map(OUTPUT_TYPE_TO_SRL);

inline const std::map<bool, std::string> KNIFE_TO_SRL = {{true, SRL_KNIFE_EQUIPPED},
                                                         {false, SRL_KNIFE_NOT_EQUIPPED}};

inline const std::map<std::string, bool> SRL_TO_KNIFE = get_inverse_map(KNIFE_TO_SRL);

inline const std::map<WeaponName, std::string> WEAPON_NAME_TO_SRL = {{WeaponName::NONE, SRL_NONE},
                                                                     {WeaponName::GLOCK, SRL_GLOCK},
                                                                     {WeaponName::AK47, SRL_AK47},
                                                                     {WeaponName::M3, SRL_M3},
                                                                     {WeaponName::AWP, SRL_AWP}};

inline const std::map<std::string, WeaponName> SRL_TO_WEAPON_NAME =
        get_inverse_map(WEAPON_NAME_TO_SRL);

inline const std::map<WeaponType, std::string> WEAPON_TYPE_TO_SRL = {
        {WeaponType::PRIMARY, SRL_AMMO_PRIMARY}, {WeaponType::SECONDARY, SRL_AMMO_SECONDARY}};

inline const std::map<std::string, WeaponType> SRL_TO_WEAPON_TYPE =
        get_inverse_map(WEAPON_TYPE_TO_SRL);
}  // namespace TextConstant

#endif
