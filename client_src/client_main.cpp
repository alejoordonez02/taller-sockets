#include <exception>
#include <iostream>
#include <cstdint>
#include <string>
#include <memory>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"

#define BUF_SIZE 512

int main(int argc, char* argv[]) {
    if (argc != 4) return -1;

    const std::string hostname = argv[1];
    const std::string servname = argv[2];
    const std::string username = argv[3];

    int ret = 0;

    Socket srv(hostname.c_str(), servname.c_str());

    /*
     * enviar el username
     ***/
    std::vector<uint8_t> srlzd_username;
    ret = Protocol::srlz_username(srlzd_username, username);

    srv.sendall(srlzd_username.data(), srlzd_username.size());

    /*
     * recibir el tipo de
     * protocolo y luego
     * instanciarlo y
     * delegarle el socket
     ***/
    char srlzd_prtcl_t[BUF_SIZE];
    srv.recvall(srlzd_prtcl_t, 2); // 2 bytes 0x06 0x07/0x08

    ProtocolType prtcl_t;
    ret = Protocol::dsrlz_prtcl_t(&prtcl_t, srlzd_prtcl_t);

    auto prtcl = Protocol::create(prtcl_t);

    /*
     * leer los comandos por
     * entrada estándar y
     * ejecutarlos
     ***/
    std::string cmd;
    while (getline(std::cin, cmd)) {
        std::vector<uint8_t> srlzd_cmd;
        ret = prtcl->srlz_cmd(srlzd_cmd, cmd);

        srv.sendall(srlzd_cmd.data(), srlzd_cmd.size());

        // srv.recv -> std::out / Printer
    }

    return ret;
}
