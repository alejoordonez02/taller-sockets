#include "../common_src/common_command.h"
#include "server_player.h"
#include "server_weapon.h"

class CommandProcessor {
private:
    Player &player;
public:
    CommandProcessor(
        Player &player);
    bool process(
        Command cmd);
};