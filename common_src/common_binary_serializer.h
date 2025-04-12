#ifndef BINARY_SERIALIZER_H
#define BINARY_SERIALIZER_H

#include <cstdint>
#include <map>
#include <vector>

#include "common_serializer.h"
#include "common_weapon_names.h"

class BinarySerializer: public Serializer {
private:
    std::map<CommandType, uint8_t> cmd_type_to_srl;
    std::map<OutputType, uint8_t> output_type_to_srl;
    std::map<WeaponName, uint8_t> weapon_name_to_srl;
    std::map<WeaponType, uint8_t> weapon_type_to_srl;
    std::map<uint8_t, CommandType> srl_to_cmd_type;
    std::map<uint8_t, OutputType> srl_to_output_type;
    std::map<uint8_t, WeaponName> srl_to_weapon_name;
    std::map<uint8_t, WeaponType> srl_to_weapon_type;

    void initialize_cmd_type_maps();
    void initialize_output_type_maps();
    void initialize_weapon_name_maps();
    void initialize_weapon_type_maps();

    void serialize_weapon_name(std::vector<uint8_t>& srlzd, const WeaponName& weapon) const;
    void serialize_number(std::vector<uint8_t>& srlzd_cmd, const int& n) const;
    int get_deserialized_number(const uint8_t& srlzd_n) const;
    void serialize_buy(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const;
    void serialize_ammo(std::vector<uint8_t>& srlzd_cmd, const Command& cmd) const;
    void serialize_equipment(std::vector<uint8_t>& srlzd_output, const Output& output) const;
    Command deserialize_buy(const std::vector<uint8_t>& srlzd_cmd) const;
    Command deserialize_ammo(const std::vector<uint8_t>& srlzd_cmd) const;
    Output deserialize_equipment(const std::vector<uint8_t>& srlzd_output) const;

public:
    /*
     * Constructor initializes maps
     * */
    BinarySerializer();

    /*
     * Commands
     * */
    CommandType get_deserialized_command_type(const std::vector<uint8_t>& srlzd_cmd) const;
    std::vector<uint8_t> serialize(const Command& cmd) const;
    Command deserialize_command(const std::vector<uint8_t>& srlzd_cmd) const;

    /*
     * Outputs
     * */
    OutputType get_deserialized_output_type(const std::vector<uint8_t>& srlzd_output) const;
    std::vector<uint8_t> serialize(const Output& output) const;
    Output deserialize_output(const std::vector<uint8_t>& srlzd_output) const;

    /*
     * Destructor
     * */
    ~BinarySerializer() = default;
};

#endif
