#include "common_binary_protocol.h"

#include <utility>
#include <vector>

#include "common_binary_serializer.h"
#include "common_socket.h"

#define MAX_BUF 32
#define CMD_HEADER_SIZE 1
#define BUY_SIZE 2
#define AMMO_SIZE 4
#define EQUIPMENT_SIZE 10

BinaryProtocol::BinaryProtocol(Socket&& skt): skt(std::move(skt)), srl(BinarySerializer()) {}

/*
 * Commands
 * */
bool BinaryProtocol::send(const Command& cmd) {
    std::vector<uint8_t> srlzd_cmd = srl.serialize(cmd);
    skt.sendall(srlzd_cmd.data(), srlzd_cmd.size());
    return !skt.is_stream_recv_closed();
}

Command BinaryProtocol::recv_command() {
    std::vector<uint8_t> srlzd_cmd(MAX_BUF);

    int r = 0;
    while (r < CMD_HEADER_SIZE) {
        r += skt.recvsome(srlzd_cmd.data() + r, srlzd_cmd.size() - r);
        if (skt.is_stream_recv_closed())
            return Command();
    }

    CommandType type = srl.get_deserialized_command_type(srlzd_cmd);

    int pending = -r;
    if (type == CommandType::BUY)
        pending += BUY_SIZE;
    else if (type == CommandType::AMMO)
        pending += AMMO_SIZE;

    if (pending)
        skt.recvall(srlzd_cmd.data() + r, pending);

    if (skt.is_stream_recv_closed())
        return Command();

    Command cmd = srl.deserialize_command(srlzd_cmd);

    return cmd;
}

/*
 * Outputs
 * */
bool BinaryProtocol::send(const Output& output) {
    std::vector<uint8_t> srlzd_output = srl.serialize(output);
    skt.sendall(srlzd_output.data(), srlzd_output.size());
    return !skt.is_stream_recv_closed();
}

Output BinaryProtocol::recv_output() {
    std::vector<uint8_t> srlzd_output(MAX_BUF);
    skt.recvall(srlzd_output.data(), EQUIPMENT_SIZE);

    if (skt.is_stream_recv_closed())
        return Output();

    Output output = srl.deserialize_output(srlzd_output);

    return output;
}
