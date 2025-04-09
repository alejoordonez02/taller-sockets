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
 * Factory
 * */
std::unique_ptr<Serializer> Serializer::create(const ProtocolType& type) {
    switch (type) {
        case ProtocolType::BINARY:
            return std::make_unique<BinarySerializer>();
        case ProtocolType::TEXT:
            return std::make_unique<TextSerializer>();
        default:
            return nullptr;
    }
}

/*
 * Username
 * */
int Serializer::serialize_username(std::vector<uint8_t>& srlzd_username,
                                   const std::string& username) {

    srlzd_username.clear();
    srlzd_username.push_back(SRL_USERNAME);

    uint16_t len = static_cast<uint16_t>(username.length());
    len = htons(len);

    uint8_t* srlzd_len = reinterpret_cast<uint8_t*>(&len);

    srlzd_username.push_back(srlzd_len[0]);
    srlzd_username.push_back(srlzd_len[1]);

    srlzd_username.insert(srlzd_username.end(), username.begin(), username.end());

    return 0;
}

int Serializer::deserialize_username(std::string& dsrzld_username,
                                     const std::vector<uint8_t>& srlzd_username) {

    const uint16_t* srlzd_len = reinterpret_cast<const uint16_t*>(&srlzd_username[1]);
    uint16_t len = ntohs(*srlzd_len);

    dsrzld_username = std::string(reinterpret_cast<const char*>(&srlzd_username[3]), len);

    return 0;
}

/*
 * Protocol type
 * */
int Serializer::serialize_protocol_type(std::vector<uint8_t>& srlzd_type,
                                        const ProtocolType& type) {

    int ret;

    srlzd_type.clear();
    srlzd_type.push_back(SRL_PROTOCOL_TYPE);

    switch (type) {
        case ProtocolType::BINARY:
            srlzd_type.push_back(SRL_BINARY);
            ret = 0;
            break;
        case ProtocolType::TEXT:
            srlzd_type.push_back(SRL_TEXT);
            ret = 0;
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}


int Serializer::deserialize_protocol_type(ProtocolType& dsrlzd_type,
                                          const std::vector<uint8_t>& srlzd_type) {

    int ret;

    switch (srlzd_type[1]) {
        case SRL_BINARY:
            dsrlzd_type = ProtocolType::BINARY;
            ret = 0;
            break;
        case SRL_TEXT:
            dsrlzd_type = ProtocolType::TEXT;
            ret = 0;
            break;
        default:
            ret = -1;
            break;
    }

    return ret;
}
