#include <iostream>
#include <cassert>
#include <string>

#include "../common_src/common_command.h"

void test_constructor_buy_awp() {
    std::string cmd_str = "buy awp";

    Type expected_type = Type::BUY;
    Weapon expected_weapon = Weapon::AWP;

    Command cmd(cmd_str);

    assert(cmd.get_t() == expected_type);
    assert(cmd.get_wpn() == expected_weapon);

    std::cout << "passed test_constructor_buy_awp()!\n";
}

void test_constructor_ammo_ak47_15() {
    std::string cmd_str = "ammo ak-47 15";

    Type expected_type = Type::AMMO;
    WeaponType expected_weapon_type = WeaponType::PRIMARY;
    int expected_count = 15;

    Command cmd(cmd_str);

    assert(cmd.get_t() == expected_type);
    assert(cmd.get_wpn_t() == expected_weapon_type);
    assert(cmd.get_count() == expected_count);

    std::cout << "passed test_constructor_ammo_ak47_15()!\n";
}

int main() {
    test_constructor_buy_awp();
    test_constructor_ammo_ak47_15();

    return 0;
}