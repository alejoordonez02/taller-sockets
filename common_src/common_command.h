#include <string>

enum Type {BUY, AMMO};
enum Weapon {GLOCK, AK47, M3, AWP};
enum WeaponType {PRIMARY, SECONDARY};

class Command {
private:
    Type t;
    Weapon wpn;
    WeaponType wpn_t;
    int count;

public:
    Command(std::string cmd);
    Type get_t();
    Weapon get_wpn();
    WeaponType get_wpn_t();
    int get_count();
};
