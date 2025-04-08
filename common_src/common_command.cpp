#include "common_command.h"
#include "common_tokenizer.h"

const std::map<std::string, CommandType> Command::s_to_cmd_type = {
    {"buy", CommandType::BUY},
    {"ammo", CommandType::AMMO}
};

const std::map<std::string, WeaponName> Command::s_to_weapon_name = {
    {"glock", WeaponName::GLOCK},
    {"ak-47", WeaponName::AK47},
    {"m3", WeaponName::M3},
    {"awp", WeaponName::AWP}
};

const std::map<std::string, WeaponType> Command::s_to_weapon_type = {
    {"glock", WeaponType::SECONDARY},
    {"ak-47", WeaponType::PRIMARY},
    {"m3", WeaponType::PRIMARY},
    {"awp", WeaponType::PRIMARY}
};

/*
 * Constructor
 * */
/*
 * From string
 * */
Command::Command(const std::string& s_cmd) {
    std::vector<std::string> cmd_tkns = Tokenizer::tknz(s_cmd);
    CommandType type = s_to_cmd_type.at(cmd_tkns[0]);

    switch(type) {
    case CommandType::BUY: {
        WeaponName weapon_name = s_to_weapon_name.at(cmd_tkns[1]);
        *this = Command(
            type,
            weapon_name);
        break;
    }
    case CommandType::AMMO: {
        WeaponType weapon_type = s_to_weapon_type.at(cmd_tkns[1]);
        int count = std::stoi(cmd_tkns[2]);
        *this = Command(
            type,
            weapon_type,
            count);
        break;
    }
    }
}

/*
 * BUY
 * */
Command::Command(
    const CommandType& type,
    const WeaponName& weapon_name)
    : type(type),
    weapon_name(weapon_name),
    weapon_type(WeaponType::NONE),
    count(0) {}

/*
 * AMMO
 * */
Command::Command(
    const CommandType& type,
    const WeaponType& weapon_type,
    const int& count)
    : type(type),
    weapon_name(WeaponName::NONE),
    weapon_type(weapon_type),
    count(count) {}

/*
 * Getters
 * */
CommandType Command::get_type() const {
    return type;
}

WeaponName Command::get_weapon_name() const {
    return weapon_name;
}

WeaponType Command::get_weapon_type() const {
    return weapon_type;
}

int Command::get_count() const {
    return count;
}

/*
 * Operator==
 * */
bool Command::operator==(
    const Command& cmd) const {

    if (type != cmd.type) return false;
    
    switch(type) {
    case CommandType::BUY:
        return (weapon_name == cmd.weapon_name);
    case CommandType::AMMO:
        return (weapon_type == cmd.weapon_type
            && count == cmd.count);
    default:
        return false;
    }
}
