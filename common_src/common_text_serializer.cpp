#include <vector>
#include <cstdint>

#include "common_text_serializer.h"
#include "common_command.h"
#include "common_output.h"

/*
 * Constructor initializes maps
 * */
TextSerializer::TextSerializer() {}

/*
 * Commands
 * */
int TextSerializer::serialize(
    std::vector<uint8_t>& srlzd_cmd,
    const Command& cmd) const {return 0;}
int TextSerializer::deserialize(
    Command& dsrlzd_cmd,
    const std::vector<uint8_t>& srlzd_cmd) const {return 0;}

/*
 * Outputs
 * */
int TextSerializer::serialize(
    std::vector<uint8_t>& srlzd_output,
    const Output& output) const {return 0;}
int TextSerializer::deserialize(
    Output& dsrlzd_output,
    const std::vector<uint8_t>& srlzd_output) const {return 0;}
