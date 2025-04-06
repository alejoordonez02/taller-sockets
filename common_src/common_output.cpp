#include <iostream>
#include <string>
#include <sstream>
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
std::string Output::output_equipment(
    Command equipment) {

    std::stringstream output;
    output << "money: $" << equipment.get_money()

        << " | knife: " << (equipment.get_knife() ? "equipped" : "not equipped")

        << " | primary: ";

        if (equipment.get_primary() == WeaponName::NONE)
            output << "not equipped";
        else
            output << weapon_name[equipment.get_primary()]
            << ", " <<  equipment.get_primary_ammo();

        output << " | secondary: ";
        if (equipment.get_secondary() == WeaponName::NONE)
            output << "not equipped";
        else
            output << weapon_name[equipment.get_secondary()]
            << ", " << equipment.get_secondary_ammo();

        output << std::endl;

    return  output.str();
}