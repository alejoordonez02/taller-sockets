#ifndef WEAPON_H
#define WEAPON_H

#include <memory>

#include "../common_src/common_weapon_names.h"

class Weapon {
protected:
    WeaponName name;
    int cost;
    int ammo;
    int ammo_cost;

public:
    Weapon(const WeaponName& name, const int& cost, const int& ammo, const int& ammo_cost);

    /*
     * Factory
     * */
    static std::unique_ptr<Weapon> create(const WeaponName& name);

    /*
     * NONE constructor
     * */
    Weapon();

    /*
     * Getters
     * */
    WeaponName get_name() const;
    int get_ammo() const;
    int get_cost() const;
    int get_ammo_cost() const;

    /*
     * Load ammo
     * */
    void load_ammo(int count);

    /*
     * Operator==
     * */
    bool operator==(const Weapon& weapon) const;
};

class Glock: public Weapon {
public:
    Glock();
};

class Ak47: public Weapon {
public:
    Ak47();
};

class M3: public Weapon {
public:
    M3();
};

class Awp: public Weapon {
public:
    Awp();
};

#endif
