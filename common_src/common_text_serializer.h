#ifndef TEXT_SERIALIZER
#define TEXT_SERIALIZER

#include <map>
#include <string>
#include <vector>

#include "common_serializer.h"

class TextSerializer: public Serializer {
private:
    void serialize_buy(std::string& srlzd_cmd, const Command& cmd) const;
    void serialize_ammo(std::string& srlzd_cmd, const Command& cmd) const;
    void serialize_equipment(std::string& srlzd_output, const Output& output) const;
    Command deserialize_buy(const std::vector<std::string>& srlzd_cmd_tkns) const;
    Command deserialize_ammo(const std::vector<std::string>& srlzd_cmd_tkns) const;
    Output deserialize_equipment(const std::vector<std::string>& slrzd_output_tkns) const;

public:
    /*
     * Constructor
     * */
    TextSerializer() = default;

    /*
     * Outputs
     * */
    std::string serialize(const Command& cmd) const;
    Command deserialize_command(const std::string& srlzd_cmd) const;

    /*
     * Outputs
     * */
    std::string serialize(const Output& output) const;
    Output deserialize_output(const std::string& srlzd_output) const;
};

#endif
