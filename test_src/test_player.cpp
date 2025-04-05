#include <iostream>
#include <cassert>
#include <optional>
#include <string>

#include "../server_src/server_player.h"
#include "../server_src/server_weapon.h"

void test_contructor_with_username() {
    Player player("mate");

    std::string expected_username = "mate";
    int expected_money = 500;
    bool expected_knife = true;
    std::optional<Weapon> expected_primary = std::nullopt;
    Weapon expected_secondary = Glock();

    assert(player.get_username() == expected_username);
    assert(player.get_money() == expected_money);
    assert(player.get_knife() == expected_knife);
    assert(player.get_primary() == expected_primary);
    assert(player.get_secondary() == expected_secondary);

    std::cout << "passed test_contructor_with_username()!\n";
}

void test_buy_ammo_secondary() {
    Player player("mate");
    int count = 15;

    int expected_count = 45;
    int expected_money = 485;

    int ret = player.buy_ammo_secondary(count);

    assert(!ret);
    assert(player.get_secondary()->get_ammo() == expected_count);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_buy_ammo_secondary()!\n";
}

void test_buy_ammo_primary_returns_false_if_non_primary() {
    Player player("mate");
    int count = 15;

    int expected_money = 500;

    int ret = player.buy_ammo_primary(count);

    assert(ret);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_buy_ammo_primary_returns_false_if_non_primary()!\n";
}

void test_buy_ammo_returns_false_if_not_enough_money() {
    Player player("mate");
    int count = 501;

    int expected_count = 30;
    int expected_money = 500;

    int ret = player.buy_ammo_secondary(count);

    assert(ret);
    assert(player.get_secondary()->get_ammo() == expected_count);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_buy_ammo_returns_false_if_not_enough_money()!\n";
}

void test_buy_primary() {
    Player player("mate");
    Ak47 weapon;

    Weapon expected_primary = weapon;
    int expected_money = 400;

    int ret = player.buy_primary(weapon);

    assert(!ret);
    assert(player.get_primary() == expected_primary);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_buy_primary()!\n";
}

int main() {
    test_contructor_with_username();
    test_buy_ammo_secondary();
    test_buy_ammo_primary_returns_false_if_non_primary();
    test_buy_ammo_returns_false_if_not_enough_money();
    test_buy_primary();

    return 0;
}