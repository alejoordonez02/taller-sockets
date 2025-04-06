#include <cassert>
#include <iostream>
#include <string>

#include "../common_src/common_output.h"
#include "../common_src/common_command.h"

void test_output_equipment() {
    Command equipment(
        Type::EQUIPMENT,
        500,
        true,
        WeaponName::AK47,
        WeaponName::GLOCK,
        30,
        90);

    std::string expected_output = 
        "money: $500 | knife: equipped | primary: ak-47, 30 | secondary: glock, 90\n";

    std::string output = Output::output_equipment(equipment);

    assert(output == expected_output);

    std::cout << "passed test_output_equipment()!\n";
}

void test_output_equipment_no_primary() {
    Command equipment(
        Type::EQUIPMENT,
        500,
        true,
        WeaponName::NONE,
        WeaponName::GLOCK,
        0,
        90);

    std::string expected_output = 
        "money: $500 | knife: equipped | primary: not equipped | secondary: glock, 90\n";

    std::string output = Output::output_equipment(equipment);

    assert(output == expected_output);

    std::cout << "passed test_output_equipment_no_primary()!\n";
}


void test_output_equipment_no_primary_no_secondary() {
    Command equipment(
        Type::EQUIPMENT,
        500,
        true,
        WeaponName::NONE,
        WeaponName::NONE,
        0,
        0);

    std::string expected_output = 
        "money: $500 | knife: equipped | primary: not equipped | secondary: not equipped\n";

    std::string output = Output::output_equipment(equipment);

    assert(output == expected_output);

    std::cout << "passed test_output_equipment_no_primary_no_secondary()!\n";
}

int main() {
    test_output_equipment();
    test_output_equipment_no_primary();
    test_output_equipment_no_primary_no_secondary();

    return 0;
}