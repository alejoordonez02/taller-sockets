#include "common_output.h"

#include <map>
#include <sstream>
#include <string>

const std::map<WeaponName, std::string> Output::weapon_name_to_s = {
        {WeaponName::NONE, "not equipped"},
        {WeaponName::GLOCK, "glock"},
        {WeaponName::AK47, "ak-47"},
        {WeaponName::M3, "m3"},
        {WeaponName::AWP, "awp"}};

/*
 * Equipment constructor
 * */
Output::Output(const OutputType& type, const int& money, const bool& knife,
               const WeaponName& primary, const int& primary_ammo, const WeaponName& secondary,
               const int& secondary_ammo):
        type(type),
        money(money),
        knife(knife),
        primary(primary),
        primary_ammo(primary_ammo),
        secondary(secondary),
        secondary_ammo(secondary_ammo) {}

/*
 * Getters
 * */

OutputType Output::get_type() const { return type; }

int Output::get_money() const { return money; }

bool Output::get_knife() const { return knife; }

WeaponName Output::get_primary() const { return primary; }

int Output::get_primary_ammo() const { return primary_ammo; }

WeaponName Output::get_secondary() const { return secondary; }

int Output::get_secondary_ammo() const { return secondary_ammo; }

/*
 * Output string
 * */
std::string Output::output_knife(bool knife) const {
    std::string output = (knife ? "equipped" : "not equipped");

    return output;
}

std::string Output::output_weapon(WeaponName weapon, int ammo) const {

    std::stringstream output;

    if (weapon == WeaponName::NONE)
        output << "not equipped";
    else
        output << weapon_name_to_s.at(weapon) << ", " << ammo;

    return output.str();
}

std::string Output::get_output() const {
    std::stringstream output;

    output << "money: $" << money << " | knife: " << output_knife(knife)
           << " | primary: " << output_weapon(primary, primary_ammo)
           << " | secondary: " << output_weapon(secondary, secondary_ammo) << std::endl;

    return output.str();
}
