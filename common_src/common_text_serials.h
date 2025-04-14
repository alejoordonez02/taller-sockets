#ifndef TEXT_SERIALS_H
#define TEXT_SERIALS_H

#include <string>

namespace TextConstant {
/*
 * Delimiters
 * */
inline const std::string DELIMITERS = ":,\n";

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
}  // namespace TextConstant

#endif
