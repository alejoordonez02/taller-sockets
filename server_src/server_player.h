#ifndef PLAYER_H
#define PLAYER_H

#include <optional>
#include <string>

#include "server_weapon.h"

class Player {
private:
    const std::string username;
    int money;
    bool knife;
    std::optional<Weapon> primary;
    std::optional<Weapon> secondary;
    int buy_ammo(
        std::optional<Weapon> &weapon,
        int count);
public:
    Player(
        const std::string &username);
    const std::string &get_username() const;
    int get_money();
    bool get_knife();
    std::optional<Weapon> get_primary();
    std::optional<Weapon> get_secondary();
    int buy_primary(
        Weapon &weapon);
    int buy_ammo_primary(
        int count);
    int buy_ammo_secondary(
        int count);
    WeaponName get_primary_name();
    WeaponName get_secondary_name();
    int get_primary_ammo();
    int get_secondary_ammo();
};

#endif
