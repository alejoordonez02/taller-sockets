#include <iostream>
#include<cassert>

#include "../server_src/server_weapon.h"

void test_new_glock_has_30_ammo_count() {
    Glock glock;

    int expected_ammo = 30;

    assert(glock.get_ammo() == expected_ammo);

    std::cout << "passed test_new_glock_has_30_ammo_count()!\n";
}

void test_load_ammo() {
    Glock glock;
    int count = 15;

    int expected_ammo = 45;

    glock.load_ammo(count);

    assert(glock.get_ammo() == expected_ammo);

    std::cout << "passed test_load_ammo()!\n";
}

int main() {
    test_new_glock_has_30_ammo_count();
    test_load_ammo();

    return 0;
}