#include <iostream>
#include <cstdint>
#include <string>
#include <exception>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"

#define BUF_SIZE 32

int main(int argc, char* argv[]) {
    if (argc != 3)
        return -1;

    const std::string servname = argv[1];
    const std::string prtcl_t = argv[2];

    Socket skt(servname.c_str());
    Socket clt = skt.accept();

    /*
     * recibir el username
     ***/
    char srlzd_username[BUF_SIZE];
    clt.recvsome(srlzd_username, sizeof(srlzd_username));

    std::string username;
    username = Protocol::dsrlz_username(srlzd_username);

    std::cout << username << " has arrived!\n";

    /*
     * enviar el tipo de
     * protocolo
     ***/
    std::string srlzd_prtcl_t;
    srlzd_prtcl_t = Protocol::srlz_prtcl_t(prtcl_t);

    clt.sendall(&srlzd_prtcl_t, sizeof(srlzd_prtcl_t));

    while (true) {
        std::string cmd_buf;
        clt.recvsome(cmd_buf.data(), BUF_SIZE);
        std::cout << cmd_buf << std::endl;
    }

    return 0;
}
