#include <exception>
#include <iostream>
#include <cstdint>
#include <string>
#include <memory>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"

int main(int argc, char* argv[]) {
    if (argc != 4) return -1;

    const std::string hostname = argv[1];
    const std::string servname = argv[2];
    const std::string username = argv[3];

    Socket srv(hostname.c_str(), servname.c_str());

    /*
     * enviar el username
     ***/
    std::string username_msg_buf;
    username_msg_buf = Protocol::srlz_username(username);

    srv.sendall(username_msg_buf.data(), username_msg_buf.size());

    /*
     * recibir el tipo de
     * protocolo y luego
     * instanciarlo
     ***/
    char prtcl_t_buf[2];
    srv.recvall(prtcl_t_buf, sizeof(prtcl_t_buf));

    std::cout << prtcl_t_buf << std::endl;

    ProtocolType prtcl_t;
    prtcl_t = Protocol::dsrlz_prtcl_t(*prtcl_t_buf);

    auto prtcl = Protocol::create(prtcl_t);

    /*
     * leer los comandos por
     * entrada estándar y
     * ejecutarlos
     ***/
    std::string cmd;
    while (getline(std::cin, cmd)) {
        if (cmd == "exit")
            return 0;

        std::string srlzd_cmd;
        srlzd_cmd = prtcl->srlz(cmd);

        std::cout << srlzd_cmd << std::endl;

        srv.sendall(srlzd_cmd.data(), srlzd_cmd.size());
    }

    return 0;
}
