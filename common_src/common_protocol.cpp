#include "common_protocol.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>

#include "common_binary_protocol.h"
// #include "common_text_protocol.h"
#include "common_command.h"
#include "common_output.h"
#include "common_serializer.h"
#include "common_socket.h"

#define MAX_BUF 32
#define USERNAME_HEADER_SIZE 3
#define PROTOCOL_TYPE_SIZE 2

/*
 * Facotry
 * */
std::unique_ptr<Protocol> Protocol::create(const ProtocolType& type, Socket&& skt) {
    switch (type) {
        case ProtocolType::BINARY:
            return std::make_unique<BinaryProtocol>(std::move(skt));
        // case ProtocolType::TEXT:
        //     return std::make_unique<TextProtocol(std::move(skt))>;
        default:
            return nullptr;
    }
}

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
        r += skt.recvsome(srlzd_username.data() + r, srlzd_username.size() - r);

    uint16_t* srlzd_len = reinterpret_cast<uint16_t*>(&srlzd_username[1]);
    int len = ntohs(*srlzd_len);

    /*
     * Ahora que ya sé la cantidad total de
     * bytes, si no llego todo con el recvsome,
     * hago recvall de los restantes
     * */
    int pending = len + USERNAME_HEADER_SIZE - r;

    if (pending)
        skt.recvall(srlzd_username.data() + r, pending);

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
