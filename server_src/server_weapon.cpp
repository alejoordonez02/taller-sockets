#include "server_weapon.h"

#include <memory>

Weapon::Weapon(const WeaponName& name, const int& cost, const int& ammo, const int& ammo_cost):
        name(name), cost(cost), ammo(ammo), ammo_cost(ammo_cost) {}

/*
 * Empty
 * */
Weapon::Weapon(): name(WeaponName::NONE), cost(0), ammo(0), ammo_cost(0) {}

/*
 * Factory
 * */
std::unique_ptr<Weapon> Weapon::create(const WeaponName& name) {
    switch (name) {
        case WeaponName::GLOCK:
            return std::make_unique<Glock>();
        case WeaponName::AK47:
            return std::make_unique<Ak47>();
        case WeaponName::M3:
            return std::make_unique<M3>();
        case WeaponName::AWP:
            return std::make_unique<Awp>();
        default:
            return std::make_unique<Weapon>();
    }
}

/*
 * Load ammo
 * */
void Weapon::load_ammo(int count) { ammo += count; }

/*
 * Getters
 * */
WeaponName Weapon::get_name() const { return name; }

int Weapon::get_ammo() const { return ammo; }

int Weapon::get_cost() const { return cost; }

int Weapon::get_ammo_cost() const { return ammo_cost; }

/*
 * Weapons
 * */
Glock::Glock(): Weapon(WeaponName::GLOCK, 100, 30, 1) {}

Ak47::Ak47(): Weapon(WeaponName::AK47, 100, 30, 1) {}

M3::M3(): Weapon(WeaponName::M3, 100, 30, 1) {}

Awp::Awp(): Weapon(WeaponName::AWP, 100, 30, 1) {}
