#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum class Type {EQUIPMENT, BUY, AMMO};
enum class WeaponName {NONE, GLOCK, AK47, M3, AWP};
enum class WeaponType {NONE, PRIMARY, SECONDARY};

class Command {             //
private:                    // refactor -> sub-
    Type t;                 // command classes &
    WeaponName wpn;         // attributes -> const
    WeaponType wpn_t;       /***/
    int count;
    int money;
    bool knife;
    WeaponName primary;
    WeaponName secondary;
    int primary_ammo;
    int secondary_ammo;

public:
    Command() = default;
    Command( // buy
        Type t,
        WeaponName wpn);
    Command( // ammo
        Type t,
        WeaponType wpn_t,
        int count);
    Command(
        std::string cmd);
    Command(
        Type t,
        int money,
        bool knife,
        WeaponName primary,
        WeaponName secondary,
        int primary_ammo,
        int secondary_ammo);
    Type get_t() const;
    WeaponName get_wpn() const;
    WeaponType get_wpn_t() const;
    int get_count() const;
    int get_money() const;
    bool get_knife() const;
    WeaponName get_primary() const;
    WeaponName get_secondary() const;
    int get_primary_ammo() const;
    int get_secondary_ammo() const;
    bool operator==(
        const Command& cmd) const;
};

#endif
