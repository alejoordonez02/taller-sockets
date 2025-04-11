#include <iostream>
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"

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
    std::cout << "username: " << username;

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
    Protocol protocol(protocol_type, std::move(skt));

    return 0;
}
