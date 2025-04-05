#include <iostream> // delegar el stdout!

#include "server_command_processor.h"
#include "../common_src/common_command.h"
#include "server_player.h"
#include "server_weapon.h"

// enum class Outputs {NOT_ENOUGH_MONEY_AMMO, ...} para delegar
// debería haber una clase Output que haga los outputs del cliente
// y del server, recibe algún OutputType y lo que tenga que outputear
// si hace falta. Podría tener dos subclases para client y server

CommandProcessor::CommandProcessor(
    Player &player) :
    player(player) {}

int CommandProcessor::process_buy(
    Command in_cmd) {

    Weapon wpn = Weapon::create(in_cmd.get_wpn());

    return player.buy_primary(wpn);
}

int CommandProcessor::process_ammo(
    Command in_cmd) {

    switch(in_cmd.get_wpn_t()) {
    case WeaponType::PRIMARY:
        return player.buy_ammo_primary(in_cmd.get_count());
    case WeaponType::SECONDARY:
        return player.buy_ammo_secondary(in_cmd.get_count());
    default:
        return -1;
    }
}

int CommandProcessor::process(
    Command &out_cmd,
    Command in_cmd) {

    int ret;

    switch(in_cmd.get_t()) {
    case Type::BUY:
        ret = process_buy(in_cmd);
        if (ret == -1)
            std::cout << "Not enough money to buy weapon\n";
        break;
    case Type::AMMO:
        ret = process_ammo(in_cmd);
        if (ret == -1)
            std::cout << "Not enough money to buy ammo\n";
        break;
    default:
        ret = -1;
        break;
    }

    Command equipment(
        Type::EQUIPMENT,
        player.get_money(),
        player.get_knife(),
        player.get_primary_name(),
        player.get_secondary_name(),
        player.get_primary_ammo(),
        player.get_secondary_ammo()
    );

    out_cmd = equipment;

    return ret;
}
