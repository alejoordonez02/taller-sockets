#include <optional>

#include "server_weapon.h"
#include "../common_src/common_weapon_names.h"

Weapon Weapon::create(
    WeaponName name) {

    switch(name) {
    case WeaponName::GLOCK:
        return Glock();
    case WeaponName::AK47:
        return Ak47();
    case WeaponName::M3:
        return M3();
    case WeaponName::AWP:
        return Awp();
    default:
        return Weapon();
    }
}

Weapon::Weapon(
    WeaponName name,
    int cost,
    int ammo_cost) :
    name(name),
    cost(cost),
    ammo(30),
    ammo_cost(ammo_cost) {}

Weapon::Weapon() :
    name(WeaponName::NONE),
    cost(0),
    ammo(0),
    ammo_cost(0) {}

WeaponName Weapon::get_name() {
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

Glock::Glock() : Weapon(WeaponName::GLOCK, 100, 1) {}

Ak47::Ak47() : Weapon(WeaponName::AK47, 100, 1) {}

M3::M3() : Weapon(WeaponName::M3, 100, 1) {}

Awp::Awp() : Weapon(WeaponName::AWP, 100, 1) {}

bool Weapon::operator==(
    const Weapon& weapon) const {

    return (name == weapon.name)
        && (cost == weapon.cost)
        && (ammo == weapon.ammo)
        && (ammo_cost == weapon.ammo_cost);
}
