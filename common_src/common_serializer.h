#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <vector>
#include <cstdint>

#include "common_protocol.h"

class Serializer {
public:
    /*
     * Username
     * */
    static int serialize_username(
        std::vector<uint8_t>& srlzd_username,
        const std::string& username);

    static int deserialize_username(
        std::string& dsrzld_username,
        const std::vector<uint8_t>& srlzd_username);

    /*
     * Protocol type
     * */
    static int serialize_protocol_type(
        std::vector<uint8_t>& srlzd_type,
        const ProtocolType& type);

    static int deserialize_protocol_type(
        ProtocolType& dsrlzd_type,
        const std::vector<uint8_t>& srlzd_type);

    /*
     * Commands
     * */
    virtual int serialize(
        std::vector<uint8_t>& srlzd_cmd,
        const Command& cmd) const = 0;
    virtual int deserialize(
        Command& dsrlzd_cmd,
        const std::vector<uint8_t>& srlzd_cmd) const = 0;

    /*
     * Outputs
     * */
    virtual int serialize(
        std::vector<uint8_t>& srlzd_output,
        const Output& output) const = 0;
    virtual int deserialize(
        Output& dsrlzd_output,
        const std::vector<uint8_t>& srlzd_output) const = 0;
};

#endif
