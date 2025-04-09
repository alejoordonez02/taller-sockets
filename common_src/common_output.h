#ifndef OUTPUT_H
#define OUTPUT_H

#include <map>
#include <string>

#include "common_weapon_names.h"

enum class OutputType { EQUIPMENT };

class Output {
private:
    static const std::map<WeaponName, std::string> weapon_name_to_s;

    const OutputType type;
    const int money;
    const bool knife;
    const WeaponName primary;
    const int primary_ammo;
    const WeaponName secondary;
    const int secondary_ammo;

    std::string output_knife(bool knife) const;
    std::string output_weapon(WeaponName weapon, int ammo) const;

public:
    /*
     * Equipment
     * */
    Output(const OutputType& type, const int& money, const bool& knife, const WeaponName& primary,
           const int& primary_ammo, const WeaponName& secondary, const int& secondary_ammo);
    /*
     * Output string
     * */
    std::string get_output() const;
};

#endif
