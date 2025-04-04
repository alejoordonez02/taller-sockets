#include <iostream>
#include <cassert>

#include "../server_src/server_command_processor.h"
#include "../common_src/common_command.h"
#include "../server_src/server_player.h"
#include "../server_src/server_weapon.h"

void test_process_buy() {
    Player player("mate");
    Command command("buy ak-47");
    CommandProcessor processor(player);

    Weapon expected_primary = Ak47();
    int expected_money = 400;

    bool ret = processor.process(command);

    assert(ret);
    assert(player.get_primary() == expected_primary);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_process_buy()!\n";
}

void test_process_ammo() {
    Player player("mate");
    Command command("ammo glock 100");
    CommandProcessor processor(player);

    int expected_count = 130;
    int expected_money = 400;

    bool ret = processor.process(command);

    assert(ret);
    assert(player.get_secondary()->get_ammo() == expected_count);
    assert(player.get_money() == expected_money);

    std::cout << "passed test_process_ammo()!\n";
}

int main() {
    test_process_buy();
    test_process_ammo();

    return 0;
}