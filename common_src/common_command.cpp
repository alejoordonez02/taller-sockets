#include <string>
#include <vector>
#include <sstream>
#include <map>

#include "common_command.h"

std::vector<std::string> tknz(
    const std::string &s) {

    std::vector<std::string> tkns;

    std::istringstream iss(s);

    std::string tkn;
    while (iss >> tkn)
        tkns.push_back(tkn);

    return tkns;
}

std::map<std::string, Type> cmd_t_map = {
    {"buy", Type::BUY},             //
    {"ammo", Type::AMMO},           //{prtcl_t??, Type::BUY},
};                                  //{username??, Type::BUY},
                                    /***/
std::map<std::string, WeaponName> wpn_map = {
    {"glock", WeaponName::GLOCK},
    {"ak-47", WeaponName::AK47},
    {"m3", WeaponName::M3},
    {"awp", WeaponName::AWP}
};

std::map<std::string, WeaponType> wpn_t_map = {
    {"glock", WeaponType::SECONDARY},
    {"ak-47", WeaponType::PRIMARY},
    {"m3", WeaponType::PRIMARY},
    {"awp", WeaponType::PRIMARY}
};

Command::Command(
    Type t,
    WeaponName wpn) :
    t(t),
    wpn(wpn),
    wpn_t(WeaponType::NONE),
    count(0) {}

Command::Command(
    Type t,
    WeaponType wpn_t,
    int count) :
    t(t),
    wpn(WeaponName::NONE),
    wpn_t(wpn_t),
    count(count) {}

Command::Command(
    std::string cmd) {

    std::vector<std::string> cmd_tkns = tknz(cmd);

    t = cmd_t_map[cmd_tkns[0]];
    switch(t) {
    case Type::BUY:
        wpn = wpn_map[cmd_tkns[1]];
        break;

    case Type::AMMO:
        wpn_t = wpn_t_map[cmd_tkns[1]];
        count = std::stoi(cmd_tkns[2]);
        break;

    default: // error
        break;
    }
}

Command::Command(
    int money,
    bool knife,
    WeaponName primary,
    WeaponName secondary,
    int primary_ammo,
    int secondary_ammo) :
    money(money),
    knife(knife),
    primary(primary),
    secondary(secondary),
    primary_ammo(primary_ammo),
    secondary_ammo(secondary_ammo) {}

Type Command::get_t() const {
    return t;    
}

WeaponName Command::get_wpn() const {
    return wpn;
}

WeaponType Command::get_wpn_t() const {
    return wpn_t;
}

int Command::get_count() const {
    return count;
}

bool Command::get_money() const {
    return money;
}

WeaponName Command::get_primary() const {
    return primary;
}

WeaponName Command::get_secondary() const {
    return secondary;
}

int Command::get_primary_ammo() const {
    return primary_ammo;
}

int Command::get_secondary_ammo() const {
    return secondary_ammo;
}

bool Command::operator==(
    const Command& cmd) const {

    if (t != cmd.t) return false;
    
    switch(t) {
    case Type::BUY:
        return (wpn == cmd.wpn);
    case Type::AMMO:
        return (wpn_t == cmd.wpn_t
            && count == cmd.count);
    default:
        return false;
    }
}
