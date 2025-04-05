#include "../common_src/common_command.h"
#include "server_player.h"
#include "server_weapon.h"

class CommandProcessor {
private:
    Player &player;
    int process_buy(
        Command in_cmd);
    int process_ammo(
        Command in_cmd);
public:
    CommandProcessor(
        Player &player);
    int process(
        Command &out_cmd,
        Command in_cmd);
};