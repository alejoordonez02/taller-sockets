#include <iostream>
#include <cstdint>
#include <string>
#include <exception>

#include "../common_src/common_socket.h"
#include "../common_src/common_protocol.h"
#include "../common_src/common_command.h"
#include "server_command_processor.h"

#define PROTOCOL_TYPE_BINARY "binary"
#define PROTOCOL_TYPE_TEXT "text"

#define BUF_SIZE 512

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
    if (prtcl_t_s == PROTOCOL_TYPE_BINARY)
        prtcl_t = ProtocolType::BINARY;
    else if (prtcl_t_s == PROTOCOL_TYPE_TEXT)
        prtcl_t = ProtocolType::TEXT;
    else
        return -1;

    auto prtcl = Protocol::create(prtcl_t);

    /*
     * instanciar el
     * player
     ***/
    Player player(username);

    /*
     * instanciar el
     * procesador
     ***/
    CommandProcessor processor(player);

    /*
     * escuchar al server
     * y actualizar el modelo
     ***/
    while (true) {
        char cmd_buf[BUF_SIZE];

        clt.recvsome(cmd_buf, sizeof(cmd_buf));
        if (clt.is_stream_recv_closed())
            return ret;

        Command cmd;
        ret = prtcl->dsrlz_cmd(cmd, cmd_buf);

        Command equipment;
        ret = processor.process(equipment, cmd);

        std::vector<uint8_t> srlzd_equipment;
        ret = prtcl->srlz_cmd(srlzd_equipment, equipment);

        clt.sendall(srlzd_equipment.data(), srlzd_equipment.size());
        if (clt.is_stream_send_closed())
            return ret;
    }

    return ret;
}
