#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "../common_src/common_command.h"
#include "../common_src/common_output.h"
#include "../common_src/common_protocol.h"
#include "../common_src/common_socket.h"

int main(int argc, const char* argv[]) {
    if (argc != 4)
        return -1;

    const std::string hostname = argv[1];
    const std::string servname = argv[2];
    const std::string username = argv[3];

    /*
     * Skt al server
     * */
    Socket skt(hostname.c_str(), servname.c_str());

    /*
     * Enviar el username
     * */
    Protocol::send_username(username, skt);

    /*
     * Recibir el tipo de protocolo e
     * instanciarlo, pasándole el
     * ownership del socket
     * */
    ProtocolType protocol_type = Protocol::recv_protocol_type(skt);
    std::unique_ptr<Protocol> protocol = Protocol::create(protocol_type, std::move(skt));

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

    return 0;
}
