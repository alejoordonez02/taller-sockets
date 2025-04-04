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

const std::string Player::get_username() {
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

bool Player::buy_primary(
    Weapon &weapon) {

    if (money < weapon.get_cost())
        return false;

    money -= weapon.get_cost();
    primary = weapon;

    return true;
}

bool Player::buy_ammo(
    std::optional<Weapon> &weapon,
    int count) {

    if (money < count * weapon->get_ammo_cost()
        || !weapon.has_value())
        return false;

    money -= count * weapon->get_ammo_cost();
    weapon->load_ammo(count);

    return true;
}

bool Player::buy_ammo_primary(
    int count) {

    return buy_ammo(primary, count);
}

bool Player::buy_ammo_secondary(
    int count) {

    return buy_ammo(secondary, count);
}
