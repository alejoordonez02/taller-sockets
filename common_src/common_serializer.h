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
     * Commands
     * */
    virtual int serialize(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const = 0;
    virtual int deserialize(Command& dsrlzd_cmd, const std::vector<uint8_t>& srlzd_cmd) const = 0;

    /*
     * Outputs
     * */
    virtual int serialize(std::vector<uint8_t>& srlzd_output, const Output& output) const = 0;
    virtual int deserialize(Output& dsrlzd_output,
                            const std::vector<uint8_t>& srlzd_output) const = 0;

    /*
     * Static methods
     * */
    /*
     * Factory
     * */
    static std::unique_ptr<Serializer> create(const ProtocolType& type);

    /*
     * Username
     * */
    static std::vector<uint8_t> serialize_username(const std::string& username);

    static int deserialize_username(std::string& dsrzld_username,
                                    const std::vector<uint8_t>& srlzd_username);

    /*
     * Protocol type
     * */
    static int serialize_protocol_type(std::vector<uint8_t>& srlzd_type, const ProtocolType& type);

    static int deserialize_protocol_type(ProtocolType& dsrlzd_type,
                                         const std::vector<uint8_t>& srlzd_type);

    /*
     * Destructor
     * */
    virtual ~Serializer() = default;
};

#endif
