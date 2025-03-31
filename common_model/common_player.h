#ifndef COMMON_PLAYER_H
#define COMMON_PLAYER_H

#include "common_weapon.h"

#include <string>
#include <optional>

class Player {
private:
    const std::string username;
    int money;
    bool knife;
    std::optional<Weapon> primary_weapon;
    std::optional<Weapon> secondary_weapon; // hardcodeada en incialización

public:
    explicit Player(const std::string &username);
    std::string get_username();
    int get_money();
    bool get_knife();
    std::string get_primary_weapon_name();
    std::string get_secondary_weapon_name();
    int get_primary_weapon_ammo();
    int get_secondary_weapon_ammo();
};

#endif
