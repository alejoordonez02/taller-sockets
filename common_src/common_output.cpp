#include <iostream>
#include <string>
#include <map>

#include "common_output.h"
#include "common_command.h"
#include "common_weapon_names.h"

std::map<WeaponName, std::string> weapon_name {
    {WeaponName::NONE, "not equipped"},
    {WeaponName::GLOCK, "glock"},
    {WeaponName::AK47, "ak-47"},
    {WeaponName::M3, "m3"},
    {WeaponName::AWP, "awp"}
};

// money: $500 | knife: equipped | primary: not_equipped | secondary: glock, 30
void Output::output_equipment(
    Command equipment) {

    std::cout << "money: $" << equipment.get_money()
        << " | knife: " << (equipment.get_knife() ? "equipped" : "not equipped")
        << " | primary: " << weapon_name[equipment.get_primary()]
        << ", " << equipment.get_primary_ammo()
        << " | secondary: " << weapon_name[equipment.get_secondary()]
        << ", " << equipment.get_secondary_ammo()
        << std::endl;
}