#ifndef WEAPON_H
#define WEAPON_H

#include <optional>

#include "../common_src/common_weapon_names.h"

class Weapon {
protected:
    WeaponName name;
    int cost;
    int ammo;
    int ammo_cost;
public:
    static Weapon create(
        WeaponName name);
    Weapon(
        WeaponName name,
        int cost,
        int ammo_cost);
    Weapon(); // none
    WeaponName get_name();
    int get_ammo();
    int get_cost();
    int get_ammo_cost();
    void load_ammo(
        int count);
    bool operator==(
        const Weapon& weapon) const;
    virtual ~Weapon() = default;
};

class Glock : public Weapon {
public:
    Glock();
};

class Ak47 : public Weapon {
public:
    Ak47();
};

class M3 : public Weapon {
public:
    M3();
};

class Awp : public Weapon {
public:
    Awp();
};

#endif
