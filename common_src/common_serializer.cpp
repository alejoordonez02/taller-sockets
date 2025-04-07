#include <string>
#include <vector>
#include <cstdint>
#include <arpa/inet.h>

#include "common_serializer.h"

int Serializer::serialize_username(
    std::vector<uint8_t>& srlzd_username,
    const std::string& username) {

    srlzd_username.clear();
    srlzd_username.push_back(0x01);

    uint16_t len = static_cast<uint16_t>(username.length());
    len = htons(len);

    uint8_t* srlzd_len = reinterpret_cast<uint8_t*>(&len);

    srlzd_username.push_back(srlzd_len[0]);
    srlzd_username.push_back(srlzd_len[1]);

    srlzd_username.insert(
        srlzd_username.end(),
        username.begin(),
        username.end());

    return 0;
}

int Serializer::serialize_protocol_type(
    std::vector<uint8_t>& srlzd_type,
    const ProtocolType& type) {

    int ret;

    srlzd_type.clear();
    srlzd_type.push_back(0x06);

    switch(type) {
    case ProtocolType::BINARY:
        srlzd_type.push_back(0x07);
        ret = 0;
        break;
    case ProtocolType::TEXT:
        srlzd_type.push_back(0x08);
        ret = 0;
        break;
    default:
        ret = -1;
        break;
    }

    return ret;
}
