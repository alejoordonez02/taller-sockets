#include "server.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "server_command_processor.h"
#include "server_player.h"

Server::Server(std::unique_ptr<Protocol>&& protocol, const std::string& username):
        protocol(std::move(protocol)), processor(std::move(Player(username))) {}

void Server::run() {
    /*
     * Recibir los comandos del cliente
     * y procesarlos
     * */
    Command cmd;
    do {
        Output equipment = processor.get_equipment();
        if (!protocol->send(equipment))
            break;

        cmd = protocol->recv_command();
        Output output = processor.process(cmd);
        if (output.get_type() == OutputType::NONE)
            break;

        std::cout << output.get_output();

    } while (!(cmd.get_type() == CommandType::NONE));
}
