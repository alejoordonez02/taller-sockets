#include <optional>
#include <string>

#include "server_player.h"
#include "server_weapon.h"

Player::Player(
    const std::string &username) :
    username(username),
    money(500),
    knife(true),
    primary(std::nullopt),
    secondary(Glock()) {}

const std::string &Player::get_username() const {
    return username;
}

int Player::get_money() {
    return money;
}

bool Player::get_knife() {
    return knife;
}

std::optional<Weapon> Player::get_primary() {
    return primary;
}

std::optional<Weapon> Player::get_secondary() {
    return secondary;
}

int Player::buy_primary(
    Weapon &weapon) {

    if (money < weapon.get_cost())
        return -1;

    money -= weapon.get_cost();
    primary = weapon;

    return 0;
}

int Player::buy_ammo(
    std::optional<Weapon> &weapon,
    int count) {

    if (money < count * weapon->get_ammo_cost()
        || !weapon.has_value())
        return -1;

    money -= count * weapon->get_ammo_cost();
    weapon->load_ammo(count);

    return 0;
}

int Player::buy_ammo_primary(
    int count) {

    return buy_ammo(primary, count);
}

int Player::buy_ammo_secondary(
    int count) {

    return buy_ammo(secondary, count);
}

WeaponName Player::get_primary_name() {
    if (!primary.has_value())
        return WeaponName::NONE;
    return primary->get_name();
}

WeaponName Player::get_secondary_name() {
    if (!secondary.has_value())
        return WeaponName::NONE;
    return secondary->get_name();
}

int Player::get_primary_ammo() {
    if (!primary.has_value())
        return 0;
    return primary->get_ammo();
}

int Player::get_secondary_ammo() {
    if (!secondary.has_value())
        return 0;
    return secondary->get_ammo();
}

