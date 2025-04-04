#include "server_weapon.h"

Weapon::Weapon(
    const std::string &name,
    int cost,
    int ammo_cost) :
    name(name),
    cost(cost),
    ammo(30),
    ammo_cost(ammo_cost) {}

std::string Weapon::get_name() {
    return name;
}

int Weapon::get_cost() {
    return cost;
}

int Weapon::get_ammo() {
    return ammo;
}

int Weapon::get_ammo_cost() {
    return ammo_cost;
}

void Weapon::load_ammo(
    int count) {

    ammo += count;
}

Glock::Glock() : Weapon("glock", 100, 1) {}

Ak47::Ak47() : Weapon("ak-47", 100, 1) {}

M3::M3() : Weapon("m3", 100, 1) {}

Awp::Awp() : Weapon("awp", 100, 1) {}

bool Weapon::operator==(
    const Weapon& weapon) const {

    return (name == weapon.name)
        && (cost == weapon.cost)
        && (ammo == weapon.ammo)
        && (ammo_cost == weapon.ammo_cost);
}
