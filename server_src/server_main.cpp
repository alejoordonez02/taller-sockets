#include <iostream>
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"
#include "server_command_processor.h"
#include "server_player.h"

int main(int argc, char* argv[]) {
    if (argc != 3) return -1;

    const std::string servname = argv[1];
    const std::string sprotocol_type = argv[2];

    /*
     * Skt al cliente
     * */
    Socket tmp(servname.c_str());
    Socket skt = tmp.accept();

    /*
     * Recibir el username
     * */
    std::string username = Protocol::recv_username(skt);
    std::cout << Output::get_username_output(username);

    /*
     * Enviar el tipo de protocolo
     * */
    ProtocolType protocol_type;

    if (sprotocol_type == "binary")
        protocol_type = ProtocolType::BINARY;
    else if(sprotocol_type == "text")
        protocol_type = ProtocolType::TEXT;
    else return -1;

    Protocol::send_protocol_type(protocol_type, skt);

    /*
     * Instanciar el protocolo,
     * delegándole el ownership
     * del socket
     * */
    std::unique_ptr<Protocol> protocol = Protocol::create(protocol_type, std::move(skt));

    /*
     * Instanciar el jugador y el
     * procesador de comandos
     * */
    Player player(username);
    CommandProcessor processor(std::move(player));

    /*
     * Recibir los comandos del
     * cliente y procesarlos
     * */
    Command cmd;
    do {
        Output equipment = processor.get_equipment();
        if(!protocol->send(equipment))
            break;

        cmd = protocol->recv_command();
        Output output = processor.process(cmd);
        if (output.get_type() == OutputType::NONE)
            break;

        std::cout << output.get_output();

    } while (!(cmd.get_type() == CommandType::NONE));

    return 0;
}
