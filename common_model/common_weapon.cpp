#include "common_weapon.h"

#include <string>

Weapon::Weapon(const std::string &name) : name(name), cost(100), ammo_cost(30) {
    ammo = 30;
}

std::string Weapon::get_name() {
    return name;
}

int Weapon::get_ammo() {
    return ammo;
}