#include "server_command_processor.h"
#include "../common_src/common_command.h"
#include "server_player.h"
#include "server_weapon.h"

CommandProcessor::CommandProcessor(
    Player &player) :
    player(player) {}

bool CommandProcessor::process(
    Command cmd) {

    switch(cmd.get_t()) {

    case Type::BUY:
        switch(cmd.get_wpn()) {
        case WeaponName::GLOCK: {
            Glock weapon;
            return player.buy_primary(weapon);
        }

        case WeaponName::AK47: {
            Ak47 weapon;
            return player.buy_primary(weapon);
        }

        case WeaponName::M3: {
            M3 weapon;
            return player.buy_primary(weapon);
        }

        case WeaponName::AWP: {
            Awp weapon;
            return player.buy_primary(weapon);
        }

        case WeaponName::NONE:
            return false;

        default:
            return false;
        }

    case Type::AMMO:
        switch(cmd.get_wpn_t()) {
        case WeaponType::PRIMARY:
            return player.buy_ammo_primary(cmd.get_count());

        case WeaponType::SECONDARY:
            return player.buy_ammo_secondary(cmd.get_count());

        default:
            return false;
        }

    default:
        return false;
    }
}
