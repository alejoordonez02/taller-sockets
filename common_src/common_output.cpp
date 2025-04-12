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
 * Empty
 * */
Output::Output():
        type(OutputType::NONE),
        money(0),
        knife(false),
        primary(WeaponName::NONE),
        primary_ammo(0),
        secondary(WeaponName::NONE),
        secondary_ammo(0) {}

/*
 * Success and not enough
 * money outputs
 * */
Output::Output(const OutputType& type): type(type) {}

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
    std::string output = (knife ? "equipped" : "not_equipped");

    return output;
}

std::string Output::output_weapon(WeaponName weapon, int ammo) const {

    std::stringstream output;

    if (weapon == WeaponName::NONE)
        output << "not_equipped";
    else
        output << weapon_name_to_s.at(weapon) << ", " << ammo;

    return output.str();
}

std::string Output::get_output_equipment() const {
    std::stringstream output;

    output << "money: $" << money << " | knife: " << output_knife(knife)
           << " | primary: " << output_weapon(primary, primary_ammo)
           << " | secondary: " << output_weapon(secondary, secondary_ammo) << std::endl;

    return output.str();
}

std::string Output::get_output_success() const { return std::string(); }

std::string Output::get_output_nem_weapon() const {
    return std::string("Not enough money to buy weapon\n");
}

std::string Output::get_output_nem_ammo() const {
    return std::string("Not enough money to buy ammo\n");
}

std::string Output::get_output() const {
    switch (type) {
        case OutputType::EQUIPMENT:
            return get_output_equipment();
        case OutputType::SUCCESS:
            return get_output_success();
        case OutputType::NEM_WEAPON:
            return get_output_nem_weapon();
        case OutputType::NEM_AMMO:
            return get_output_nem_ammo();
        default:
            return std::string();
    }
}

/*
 * Username
 * */
std::string Output::get_username_output(const std::string& username) {
    std::stringstream output;
    output << username << " has arrived!" << std::endl;

    return output.str();
}

/*
 * Operator==
 * */
bool Output::operator==(const Output& output) const {

    if (type != output.type)
        return false;

    switch (type) {
        case OutputType::EQUIPMENT:
            return (money == output.money && knife == output.knife && primary == output.primary &&
                    primary_ammo == output.primary_ammo && secondary == output.secondary &&
                    secondary_ammo == output.secondary_ammo);
        default:
            return false;
    }
}
