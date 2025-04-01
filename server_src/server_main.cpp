#include <iostream>
#include <cstdint>
#include <string>
#include <exception>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"
#include "../common_src/common_command.h"
#include "common_command_processor.h"

#define BUF_SIZE 32

int main(int argc, char* argv[]) {
    if (argc != 3)
        return -1;

    const std::string servname = argv[1];
    const std::string prtcl_t_s = argv[2];

    int ret = 0;

    Socket skt(servname.c_str());
    Socket clt = skt.accept();

    /*
     * recibir el username
     ***/
    char srlzd_username[BUF_SIZE];
    clt.recvsome(srlzd_username, sizeof(srlzd_username));

    std::string username;
    ret = Protocol::dsrlz_username(username, srlzd_username);

    std::cout << username << " has arrived!\n";

    /*
     * enviar el tipo de
     * protocolo
     ***/
    std::vector<uint8_t> srlzd_prtcl_t;
    ret = Protocol::srlz_prtcl_t(srlzd_prtcl_t, prtcl_t_s);

    clt.sendall(srlzd_prtcl_t.data(), srlzd_prtcl_t.size());

    /*
     * instanciar el
     * protocolo
     ***/
    ProtocolType prtcl_t;
    ret = Protocol::dsrlz_prtcl_t(&prtcl_t, srlzd_prtcl_t);

    auto prtcl = Protocol::create(prtcl_t);

    /*
     * escuchar al server
     * y actualizar el modelo
     ***/
    while (true) {
        std::vector<uint8_t> cmd_buf;

        clt.recvsome(cmd_buf.data(), BUF_SIZE);
        if (clt.is_stream_recv_closed())
            return ret;

        Command cmd;
        ret = prtcl->dsrlz_cmd(cmd, cmd_buf);

        // CommandProcessor(cmd) -> actualizar el modelo

        // clt.sendsome equipment
        // if (clt.is_stream_send_closed())
        //     return ret;
    }

    return ret;
}
