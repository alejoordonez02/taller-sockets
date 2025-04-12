#include "common_text_protocol.h"
#include "common_text_serializer.h"

// si éstos fueran atributos de instancia entonces podría usar polimorfismo...
// pensándolo bien, creo que éste protocolo debería aprovechar el hecho de que todos los mensajes
// terminan en \n...
#define MAX_BUF 256
// #define CMD_HEADER_SIZE 1
// #define BUY_SIZE 2
// #define AMMO_SIZE 4
// #define EQUIPMENT_SIZE 10

TextProtocol::TextProtocol(Socket&& skt): skt(std::move(skt)), srl(TextSerializer()) {}

/*
 * Commands
 * */
bool TextProtocol::send(const Command& cmd) {
    std::string srlzd_cmd = srl.serialize(cmd);
    skt.sendall(srlzd_cmd.data(), srlzd_cmd.size());
    return !skt.is_stream_recv_closed();
}

Command TextProtocol::recv_command() { // ésta función es idéntica a la de binary, una vez que pasen los tests debería refactorizar...
    std::string srlzd_cmd(MAX_BUF, '\0');

    int r = 0; 
    while (srlzd_cmd.find('\n') == std::string::npos) {
        r += skt.recvsome(srlzd_cmd.data(), srlzd_cmd.size() - r);
        if (skt.is_stream_recv_closed())
            return Command();
    }

    Command cmd = srl.deserialize_command(srlzd_cmd);

    return cmd;
}

/*
 * Outputs
 * */
bool TextProtocol::send(const Output& output) {
    std::string srlzd_output = srl.serialize(output);
    skt.sendall(srlzd_output.data(), srlzd_output.size());
    return !skt.is_stream_recv_closed();
}

Output TextProtocol::recv_output() {
    std::string srzld_output(MAX_BUF, '\0');

    int r = 0; 
    while (srzld_output.find('\n') == std::string::npos) {
        r += skt.recvsome(srzld_output.data(), srzld_output.size() - r);
        if (skt.is_stream_recv_closed())
            return Output();
    }

    Output output = srl.deserialize_output(srzld_output);

    return output;
}