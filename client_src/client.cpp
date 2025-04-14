#include "client.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/common_command.h"
#include "../common_src/common_output.h"
#include "../common_src/common_protocol.h"

Client::Client(std::unique_ptr<Protocol>&& protocol): protocol(std::move(protocol)) {}

void Client::run() {
    std::string scmd;
    while (true) {

        /*
         * Recibir salidas e imprimirlas
         * */
        Output equipment = protocol->recv_output();
        std::cout << equipment.get_output();

        /*
         * Leer comandos
         * */
        if (!getline(std::cin, scmd) || scmd == "exit")
            break;

        /*
         * Enviar comandos
         * */
        Command cmd(scmd);
        protocol->send(cmd);
    }
}
