#include <iostream>

#include "server_command_processor.h"
#include "server_player.h"
#include "server_weapon.h"
#include "../common_src/common_command.h"
#include "../common_src/common_weapon_names.h"

CommandProcessor::CommandProcessor(Player&& player) : player(std::move(player)) {};

Output CommandProcessor::process_buy(const Command& cmd) {
    std::unique_ptr<Weapon> weapon = Weapon::create(cmd.get_weapon_name());
    bool ret = player.buy_primary(std::move(weapon));
    if (ret)
        return Output(OutputType::SUCCESS);
    return Output(OutputType::NEM_WEAPON);
}

Output CommandProcessor::process_ammo(const Command& cmd) {
    int count = cmd.get_count();
    bool ret;

    switch (cmd.get_weapon_type()) {
    case WeaponType::PRIMARY:
        ret = player.buy_primary_ammo(count);
        break;
    case WeaponType::SECONDARY:
        ret = player.buy_secondary_ammo(count);
        break;
    default:
        return Output();
    }

    if (ret)
        return Output(OutputType::SUCCESS);
    return Output(OutputType::NEM_AMMO);
}

Output CommandProcessor::process(const Command& cmd) {
    switch(cmd.get_type()) {
    case CommandType::BUY:
        return process_buy(cmd);
    case CommandType::AMMO:
        return process_ammo(cmd);
    default:
        return Output();
    }
}

Output CommandProcessor::get_equipment() const {
    Output equipment(OutputType::EQUIPMENT, player.get_money(), player.get_knife(), player.get_primary_name(),
                     player.get_ammo_primary(), player.get_secondary_name(), player.get_ammo_secondary());

    return equipment;
}