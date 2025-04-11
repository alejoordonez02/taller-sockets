#include "common_protocol.h"

#include <string>
#include <vector>

#include <arpa/inet.h>

#include "common_command.h"
#include "common_output.h"
#include "common_serializer.h"
#include "common_socket.h"

#define MAX_BUF 32
#define USERNAME_HEADER_SIZE 3
#define PROTOCOL_TYPE_SIZE 2

/*
 * Constructor
 * */
Protocol::Protocol(const ProtocolType& type, Socket&& skt) : skt(std::move(skt)) {};

/*
 * Commands
 * */
int Protocol::send(const Command& cmd) { return 0; }
int Protocol::recv(Command& cmd) { return 0; }

/*
 * Outputs
 * */
int Protocol::send(const Output& output) { return 0; }
int Protocol::recv(Output& output) { return 0; }

/*
 * Static methods
 * */
/*
 * Send username
 * */
void Protocol::send_username(const std::string& username, Socket& skt) {
    std::vector<uint8_t> srlzd_username = Serializer::serialize_username(username);
    skt.sendall(srlzd_username.data(), srlzd_username.size());
}

std::string Protocol::recv_username(Socket& skt) {
    std::vector<uint8_t> srlzd_username(MAX_BUF);

    int r = 0;

    /*
     * Me aseguro de haber recibido el length
     * del username
     * */
    while (r < USERNAME_HEADER_SIZE)
        r += skt.recvsome(srlzd_username.data(), srlzd_username.size());

    uint16_t* srlzd_len = reinterpret_cast<uint16_t*>(&srlzd_username[1]);
    int len = ntohs(*srlzd_len);

    /*
     * Ahora que ya sé la cantidad total de
     * bytes, si no llego todo con el recvsome,
     * hago recvall de los restantes
     * */
    if (r < len + USERNAME_HEADER_SIZE)
        skt.recvall(srlzd_username.data() + r, len + USERNAME_HEADER_SIZE - r);

    std::string username = Serializer::deserialize_username(srlzd_username);

    return username;
}

/*
 * Send protocol type
 * */
void Protocol::send_protocol_type(const ProtocolType& type, Socket& skt) {
    std::vector<uint8_t> srlzd_protocol_type = Serializer::serialize_protocol_type(type);
    skt.sendall(srlzd_protocol_type.data(), srlzd_protocol_type.size());
}

ProtocolType Protocol::recv_protocol_type(Socket& skt) {
    std::vector<uint8_t> srlzd_protocol_type(PROTOCOL_TYPE_SIZE);
    skt.recvall(srlzd_protocol_type.data(), srlzd_protocol_type.size());
    ProtocolType dsrlzd_protocol_type = Serializer::deserialize_protocol_type(srlzd_protocol_type);

    return dsrlzd_protocol_type;
}
