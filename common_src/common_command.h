#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>

#include "common_weapon_names.h"
#include "common_tokenizer.h"

enum class CommandType {BUY, AMMO};

class Command {
private:
    static const std::map<std::string, CommandType> s_to_cmd_type;
    static const std::map<std::string, WeaponName> s_to_weapon_name;
    static const std::map<std::string, WeaponType> s_to_weapon_type;

    CommandType type;
    WeaponName weapon_name;
    WeaponType weapon_type;
    int count;
public:
    /*
     * From string
     * */
    Command(const std::string& s_cmd);

    /*
     * BUY
     * */
    Command(
        const CommandType& type,
        const WeaponName& weapon_name);

    /*
     * AMMO
     * */
    Command(
        const CommandType& type,
        const WeaponType& weapon_type,
        const int& count);

    /*
     * Operator==
     * */
    bool operator==(const Command& cmd) const;
};

#endif
