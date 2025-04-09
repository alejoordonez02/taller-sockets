#ifndef BINARY_SERIALIZER_H
#define BINARY_SERIALIZER_H

#include <map>
#include <cstdint>

#include "common_serializer.h"
#include "common_weapon_names.h"

class BinarySerializer : public Serializer {
private:
    std::map<CommandType, uint8_t> cmd_type_to_srl;
    std::map<OutputType, uint8_t> output_to_srl;
    std::map<WeaponName, uint8_t> weapon_name_to_srl;
    std::map<WeaponType, uint8_t> weapon_type_to_srl;
    std::map<uint8_t, CommandType> srl_to_cmd_type;
    std::map<uint8_t, OutputType> srl_to_output;
    std::map<uint8_t, WeaponName> srl_to_weapon_name;
    std::map<uint8_t, WeaponType> srl_to_weapon_type;

    void initialize_cmd_type_maps();
    void initialize_output_maps();
    void initialize_weapon_name_maps();
    void initialize_weapon_type_maps();

    std::vector<uint8_t> get_serialized_number(int n) const;
    int serialize_buy(
        std::vector<uint8_t>& srlzd_cmd,
        const Command& cmd) const;
    int serialize_ammo(
        std::vector<uint8_t>& srlzd_cmd,
        const Command& cmd) const;
public:
    /*
     * Constructor initializes maps
     * */
    BinarySerializer();

    /*
     * Commands
     * */
    int serialize(
        std::vector<uint8_t>& srlzd_cmd,
        const Command& cmd) const override;
    int deserialize(
        Command& dsrlzd_cmd,
        const std::vector<uint8_t>& srlzd_cmd) const override;

    /*
     * Outputs
     * */
    int serialize(
        std::vector<uint8_t>& srlzd_output,
        const Output& output) const override;
    int deserialize(
        Output& dsrlzd_output,
        const std::vector<uint8_t>& srlzd_output) const override;

    /*
     * Destructor
     * */
    ~BinarySerializer() = default;
};

#endif
