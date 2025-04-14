#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "common_command.h"
#include "common_output.h"
#include "common_protocol_types.h"

class Serializer {
public:
    /*
     * Static methods
     * */
    /*
     * Username
     * */
    static std::vector<uint8_t> serialize_username(const std::string& username);

    static std::string deserialize_username(const std::vector<uint8_t>& srlzd_username);

    /*
     * Protocol type
     * */
    static std::vector<uint8_t> serialize_protocol_type(const ProtocolType& type);

    static ProtocolType deserialize_protocol_type(const std::vector<uint8_t>& srlzd_type);
};

#endif
