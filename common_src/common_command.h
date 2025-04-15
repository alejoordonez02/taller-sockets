#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>
#include <vector>

#include "common_tokenizer.h"
#include "common_weapon_names.h"

enum class CommandType { NONE, EXIT, BUY, AMMO };

class Command {
private:
    static const std::map<std::string, CommandType> s_to_cmd_type;
    static const std::map<std::string, WeaponName> s_to_weapon_name;
    static const std::map<std::string, WeaponType> s_to_weapon_type;

    CommandType type;
    WeaponName weapon_name;
    WeaponType weapon_type;
    int count;

    static CommandType get_type(const std::vector<std::string>& cmd_tkns);
    static WeaponName get_weapon_name(const std::vector<std::string>& cmd_tkns);
    static WeaponType get_weapon_type(const std::vector<std::string>& cmd_tkns);
    static int get_count(const std::vector<std::string>& cmd_tkns);

public:
    Command();
    /*
     * From string
     * */
    explicit Command(const std::string& s_cmd);

    /*
     * With type
     * */
    explicit Command(const CommandType& type);

    /*
     * BUY
     * */
    Command(const CommandType& type, const WeaponName& weapon_name);

    /*
     * AMMO
     * */
    Command(const CommandType& type, const WeaponType& weapon_type, const int& count);

    /*
     * Getters
     * */
    CommandType get_type() const;
    WeaponName get_weapon_name() const;
    WeaponType get_weapon_type() const;
    int get_count() const;


    /*
     * Operator==
     * */
    bool operator==(const Command& cmd) const;
};

#endif
