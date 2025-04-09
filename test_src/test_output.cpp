#include <cassert>
#include <iostream>
#include <string>

#include "../common_src/common_output.h"
#include "../common_src/common_weapon_names.h"

void test00_output_full_equipment_returns_expected_output() {
    Output output(
    OutputType::EQUIPMENT,
    2000,
    true,
    WeaponName::M3,
    90,
    WeaponName::GLOCK,
    30);

    std::string expected_output =
    "money: $2000 | knife: equipped | primary: m3, 90 | secondary: glock, 30\n";

    std::string soutput = output.get_output();

    assert(soutput == expected_output);

    std::cout << "Passed 00!\n";
}

void test01_output_empty_equipment_returns_expected_output() {
    Output output(
    OutputType::EQUIPMENT,
    0,
    false,
    WeaponName::NONE,
    0,
    WeaponName::NONE,
    0);

    std::string expected_output =
    "money: $0 | knife: not equipped | primary: not equipped | secondary: not equipped\n";

    std::string soutput = output.get_output();

    assert(soutput == expected_output);

    std::cout << "Passed 01!\n";
}

int main() {
    test00_output_full_equipment_returns_expected_output();
    test01_output_empty_equipment_returns_expected_output();

    return 0;
}
