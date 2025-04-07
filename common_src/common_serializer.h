#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>
#include <cstdint>

#include "common_protocol.h"

class Serializer {
public:
    static int serialize_username(
        std::vector<uint8_t>& srlzd_username,
        const std::string& username);
    static int serialize_protocol_type(
        std::vector<uint8_t>& srlzd_type,
        const ProtocolType& type);
};

#endif
