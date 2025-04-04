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
    bool buy_ammo(
        std::optional<Weapon> &weapon,
        int count);
public:
    Player(
        const std::string &username);
    const std::string get_username();
    int get_money();
    bool get_knife();
    std::optional<Weapon> get_primary();
    std::optional<Weapon> get_secondary();
    bool buy_primary(
        Weapon &weapon);
    bool buy_ammo_primary(
        int count);
    bool buy_ammo_secondary(
        int count);
};

#endif
