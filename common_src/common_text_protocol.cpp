#include "common_text_protocol.h"

#include <algorithm>
#include <string>
#include <utility>

#include "common_text_serializer.h"

#define MAX_BUF 256
#define EQUIPMENT_LINES 4

TextProtocol::TextProtocol(Socket&& skt): skt(std::move(skt)), srl(TextSerializer()) {}

/*
 * Commands
 * */
bool TextProtocol::send(const Command& cmd) {
    std::string srlzd_cmd = srl.serialize(cmd);
    skt.sendall(srlzd_cmd.data(), srlzd_cmd.size());
    return !skt.is_stream_recv_closed();
}

Command TextProtocol::recv_command() {
    std::string srlzd_cmd(MAX_BUF, '\0');

    int r = 0;
    while (srlzd_cmd.find('\n') == std::string::npos) {
        r += skt.recvsome(srlzd_cmd.data() + r, srlzd_cmd.size() - r);
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
    std::string srlzd_output(MAX_BUF, '\0');

    int r = 0;
    int l = 0;
    while (l < EQUIPMENT_LINES) {
        r += skt.recvsome(srlzd_output.data() + r, srlzd_output.size() - r);
        l = std::count(srlzd_output.begin(), srlzd_output.end(), '\n');
        if (skt.is_stream_recv_closed())
            return Output();
    }

    Output output = srl.deserialize_output(srlzd_output);

    return output;
}
