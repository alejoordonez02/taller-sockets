#include "common_player.h"
#include "common_weapon.h"

#include <string>
#include <optional>

Player::Player(const std::string &username) :
        username(username),
        money(500),
        knife(true),
        primary_weapon(std::nullopt),
        secondary_weapon("glock") {
}

std::string Player::get_username() {
    return username;
}

int Player::get_money() {
    return money;
}

bool Player::get_knife() {
    return knife;
}

std::string Player::get_primary_weapon_name() {
    return primary_weapon->get_name();
}

std::string Player::get_secondary_weapon_name() {
    return secondary_weapon->get_name();
}

int Player::get_primary_weapon_ammo() {
    return primary_weapon->get_ammo();
}

int Player::get_secondary_weapon_ammo() {
    return secondary_weapon->get_ammo();
}
