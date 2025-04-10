#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"

int main(int argc, char* argv[]) {
    if (argc != 4) return -1;

    const std::string hostname = argv[1];
    const std::string servname = argv[2];
    const std::string username = argv[3];

    /*
     * Skt al server
     * */
    Socket skt(servname);

    /*
     * Enviar el username
     * */
    Protocol::send_username(username, skt);

    /*
     * Recibir el tipo de protocolo e
     * instanciarlo
     * */
    ProtocolType protocol_type = Protocol::recv_protocol_type(skt);
    Protocol protocol(protocol_type, skt);

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
        Output output = protocol.receive_output();
        output.output();
    }

    return 0;
}