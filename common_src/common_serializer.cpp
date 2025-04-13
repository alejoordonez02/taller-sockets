#include "common_serializer.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "common_binary_serializer.h"
#include "common_command.h"
#include "common_output.h"
#include "common_protocol.h"
#include "common_text_serializer.h"

#define SRL_USERNAME 0x01
#define SRL_PROTOCOL_TYPE 0x06

#define SRL_BINARY 0x07
#define SRL_TEXT 0x08

/*
 * Static methods
 * */
/*
 * Username
 * */
std::vector<uint8_t> Serializer::serialize_username(const std::string& username) {
    std::vector<uint8_t> srlzd_username;

    srlzd_username.push_back(SRL_USERNAME);

    uint16_t len = static_cast<uint16_t>(username.length());
    len = htons(len);

    uint8_t* srlzd_len = reinterpret_cast<uint8_t*>(&len);

    srlzd_username.push_back(srlzd_len[0]);
    srlzd_username.push_back(srlzd_len[1]);

    srlzd_username.insert(srlzd_username.end(), username.begin(), username.end());

    return srlzd_username;
}

std::string Serializer::deserialize_username(const std::vector<uint8_t>& srlzd_username) {

    const uint16_t* srlzd_len = reinterpret_cast<const uint16_t*>(&srlzd_username[1]);
    uint16_t len = ntohs(*srlzd_len);

    std::string dsrzld_username(reinterpret_cast<const char*>(&srlzd_username[3]), len);

    return dsrzld_username;
}

/*
 * Protocol type
 * */
std::vector<uint8_t> Serializer::serialize_protocol_type(const ProtocolType& type) {
    std::vector<uint8_t> srlzd_type;

    srlzd_type.push_back(SRL_PROTOCOL_TYPE);

    switch (type) {
        case ProtocolType::BINARY:
            srlzd_type.push_back(SRL_BINARY);
            break;
        case ProtocolType::TEXT:
            srlzd_type.push_back(SRL_TEXT);
            break;
        default:
            break;
    }

    return srlzd_type;
}


ProtocolType Serializer::deserialize_protocol_type(const std::vector<uint8_t>& srlzd_type) {
    switch (srlzd_type[1]) {
        case SRL_BINARY:
            return ProtocolType::BINARY;
        case SRL_TEXT:
            return ProtocolType::TEXT;
        default:
            return ProtocolType::NONE;
    }
}
