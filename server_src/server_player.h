#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "server_weapon.h"

class Player {
private:
    const std::string username;
    int money;
    bool knife;
    std::unique_ptr<Weapon> primary;
    std::unique_ptr<Weapon> secondary;

    bool buy_ammo(std::unique_ptr<Weapon>& weapon, int& count);

public:
    /*
     * Constructor
     * */
    explicit Player(const std::string& username);

    /*
     * Buy
     * */
    bool buy_primary(std::unique_ptr<Weapon>&& weapon);

    /*
     * Ammo
     * */
    bool buy_primary_ammo(int& count);
    bool buy_secondary_ammo(int& count);

    /*
     * Getters
     * */
    int get_money() const;
    bool get_knife() const;
    WeaponName get_primary_name() const;
    int get_ammo_primary() const;
    WeaponName get_secondary_name() const;
    int get_ammo_secondary() const;
};

#endif
