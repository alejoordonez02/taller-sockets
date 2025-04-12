#ifndef OUTPUT_H
#define OUTPUT_H

#include <map>
#include <string>

#include "common_weapon_names.h"

enum class OutputType { NONE, SUCCESS, NEM_WEAPON, NEM_AMMO, EQUIPMENT };

class Output {
private:
    static const std::map<WeaponName, std::string> weapon_name_to_s;

    OutputType type;
    int money;
    bool knife;
    WeaponName primary;
    int primary_ammo;
    WeaponName secondary;
    int secondary_ammo;

    std::string output_knife(bool knife) const;
    std::string output_weapon(WeaponName weapon, int ammo) const;
    std::string get_output_equipment() const;
    std::string get_output_success() const;
    std::string get_output_nem_weapon() const;
    std::string get_output_nem_ammo() const;

public:
    /*
     * None
     * */
    Output();

    /*
     * Success and not enough
     * money outputs
     * */
    Output(const OutputType& type);

    /*
     * Equipment
     * */
    Output(const OutputType& type, const int& money, const bool& knife, const WeaponName& primary,
           const int& primary_ammo, const WeaponName& secondary, const int& secondary_ammo);

    /*
     * Getters
     * */
    OutputType get_type() const;
    int get_money() const;
    bool get_knife() const;
    WeaponName get_primary() const;
    int get_primary_ammo() const;
    WeaponName get_secondary() const;
    int get_secondary_ammo() const;

    /*
     * Output string
     * */
    std::string get_output() const;

    /*
     * Username
     * */
    static std::string get_username_output(const std::string& username);

    /*
     * Operator==
     * */
    bool operator==(const Output& output) const;
};

#endif
