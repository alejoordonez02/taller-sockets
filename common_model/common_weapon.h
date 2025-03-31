#ifndef COMMON_WEAPON_H
#define COMMON_WEAPON_H

#include <string>

class Weapon {
private:
    const std::string name;
    const int cost; // hardcodeado
    const int ammo_cost; // hardcodeado
    int ammo; // hardcodeado

public:
    explicit Weapon(const std::string &name);
    std::string get_name();
    int get_ammo();
    void load_ammo(int ammo);
};

#endif
