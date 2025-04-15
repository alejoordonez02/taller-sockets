#include "client.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/common_command.h"
#include "../common_src/common_output.h"
#include "../common_src/common_protocol.h"

Client::Client(std::unique_ptr<Protocol>&& protocol): protocol(std::move(protocol)) {}

Command Client::get_command() {
    std::string scmd;
    if (!getline(std::cin, scmd))
        return Command(CommandType::EXIT);

    return Command(scmd);
}

void Client::run() {
    while (true) {

        /*
         * Recibir salidas e imprimirlas
         * */
        Output equipment = protocol->recv_output();
        std::cout << equipment.get_output();

        /*
         * Leer comandos
         * */
        Command cmd;
        while (cmd.get_type() == CommandType::NONE) {
            cmd = get_command();
        }

        if (cmd.get_type() == CommandType::EXIT)
            break;

        /*
         * Enviar comandos
         * */
        protocol->send(cmd);
    }
}
