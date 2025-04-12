#include "server_player.h"
#include "../common_src/common_weapon_names.h"

/*
 * Constructor
 * */
Player::Player(const std::string& username) : username(username), money(500), knife(true),
               primary(Weapon::create(WeaponName::NONE)), secondary(Weapon::create(WeaponName::GLOCK)){}

/*
 * Buy primary
 * */
bool Player::buy_primary(std::unique_ptr<Weapon>&& weapon) {
    int cost = weapon->get_cost();
    if (money < cost)
        return false;
    money -= cost;
    primary = std::move(weapon);
    return true;
}

/*
 * Ammo
 * */
bool Player::buy_ammo(std::unique_ptr<Weapon>& weapon, int& count) {
    int cost = count * weapon->get_ammo_cost();
    if (money < cost)
        return false;
    money -= cost;
    weapon->load_ammo(count);
    return true;
}

bool Player::buy_primary_ammo(int& count) {
    return buy_ammo(primary, count);
}

bool Player::buy_secondary_ammo(int& count) {
    return buy_ammo(secondary, count);
}

/*
 * Getters
 * */
int Player::get_money() const {
    return money;
}

bool Player::get_knife() const {
    return knife;
}

WeaponName Player::get_primary_name() const {
    return primary->get_name();
}

int Player::get_ammo_primary() const {
    return primary->get_ammo();
}

WeaponName Player::get_secondary_name() const {
    return secondary->get_name();
}

int Player::get_ammo_secondary() const {
    return secondary->get_ammo();
}
