#include <iostream>
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"
#include "../common_src/common_command.h"
#include "../common_src/common_output.h"

int main(int argc, char* argv[]) {
    if (argc != 4) return -1;

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

    if (protocol_type == ProtocolType::BINARY)
      std::cout << "binary!\n";

    Protocol protocol(protocol_type, std::move(skt));

    std::string scmd;
    while (getline(std::cin, scmd)) {
    /*
     * Enviar comandos
     * */
        Command cmd(scmd);
        protocol.send(cmd);

    /*
     * Recibir salidas e imprimirlas
     * */
        // Output output = protocol.receive_output();
        // output.output();
    }

    return 0;
}