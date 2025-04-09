#ifndef TEXT_SERIALIZER
#define TEXT_SERIALIZER

#include <vector>

#include "common_serializer.h"

class TextSerializer: public Serializer {
public:
    /*
     * Constructor initializes maps
     * */
    TextSerializer();

    /*
     * Commands
     * */
    int serialize(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const override;
    int deserialize(Command& dsrlzd_cmd, const std::vector<uint8_t>& srlzd_cmd) const override;

    /*
     * Outputs
     * */
    int serialize(std::vector<uint8_t>& srlzd_output, const Output& output) const override;
    int deserialize(Output& dsrlzd_output, const std::vector<uint8_t>& srlzd_output) const override;
};

#endif
