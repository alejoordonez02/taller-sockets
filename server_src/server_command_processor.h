#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "../common_src/common_command.h"
#include "../common_src/common_output.h"

#include "server_player.h"
#include "server_weapon.h"

class CommandProcessor {
private:
    Player player;
    Output process_buy(const Command& cmd);
    Output process_ammo(const Command& cmd);

public:
    explicit CommandProcessor(Player&& player);
    Output process(const Command& cmd);
    Output get_equipment() const;
};

#endif
