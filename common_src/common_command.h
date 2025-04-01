#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum class Type {BUY, AMMO};
enum class Weapon {NONE, GLOCK, AK47, M3, AWP};
enum class WeaponType {NONE, PRIMARY, SECONDARY};

class Command {
private:
    Type t;
    Weapon wpn;
    WeaponType wpn_t;
    int count;

public:
    Command() = default;
    Command( // buy
        Type t,
        Weapon wpn);
    Command( // ammo
        Type t,
        WeaponType wpn_t,
        int count);
    Command(
        std::string cmd);
    Type get_t() const;
    Weapon get_wpn() const;
    WeaponType get_wpn_t() const;
    int get_count() const;
    bool operator==(
        const Command& cmd) const;
};

#endif
