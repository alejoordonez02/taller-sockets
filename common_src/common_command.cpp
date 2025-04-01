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
std::map<std::string, Weapon> wpn_map = {
    {"glock", Weapon::GLOCK},
    {"ak-47", Weapon::AK47},
    {"m3", Weapon::M3},
    {"awp", Weapon::AWP}
};

std::map<std::string, WeaponType> wpn_t_map = {
    {"glock", WeaponType::SECONDARY},
    {"ak-47", WeaponType::PRIMARY},
    {"m3", WeaponType::PRIMARY},
    {"awp", WeaponType::PRIMARY}
};

Command::Command(
    std::string cmd) {

    std::vector<std::string> cmd_tkns = tknz(cmd);

    t = cmd_t_map[cmd_tkns[0]];
    switch(t) {
    case BUY:
        wpn = wpn_map[cmd_tkns[1]];
        break;

    case AMMO:
        wpn_t = wpn_t_map[cmd_tkns[1]];
        count = std::stoi(cmd_tkns[2]);
        break;
    }
}

Type Command::get_t() {
    return t;    
}

Weapon Command::get_wpn() {
    return wpn;
}

WeaponType Command::get_wpn_t() {
    return wpn_t;
}

int Command::get_count() {
    return count;
}
