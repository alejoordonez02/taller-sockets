#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"

#include "server.h"
#include "server_command_processor.h"
#include "server_player.h"

int main(int argc, const char* argv[]) {
    if (argc != 3)
        return -1;

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
    else if (sprotocol_type == "text")
        protocol_type = ProtocolType::TEXT;
    else
        return -1;

    Protocol::send_protocol_type(protocol_type, skt);

    /*
     * Instanciar el protocolo, delegándole
     * el ownership del socket
     * */
    std::unique_ptr<Protocol> protocol = Protocol::create(protocol_type, std::move(skt));

    /*
     * Instanciar el server, delegarle el
     * protocolo, y correrlo
     * */
    Server server(std::move(protocol), username);
    server.run();

    return 0;
}
