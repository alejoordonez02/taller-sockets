#ifndef TEXT_SERIALIZER
#define TEXT_SERIALIZER

#include <string>
#include <vector>

#include "common_serializer.h"

class TextSerializer: public Serializer {
private:
    std::map<CommandType, std::string> cmd_type_to_srl;
    std::map<OutputType, std::string> output_type_to_srl;
    std::map<bool, std::string> knife_to_srl;
    std::map<WeaponName, std::string> weapon_name_to_srl;
    std::map<WeaponType, std::string> weapon_type_to_srl;
    std::map<std::string, CommandType> srl_to_cmd_type;
    std::map<std::string, OutputType> srl_to_output_type;
    std::map<std::string, bool> srl_to_knife;
    std::map<std::string, WeaponName> srl_to_weapon_name;
    std::map<std::string, WeaponType> srl_to_weapon_type;

    void initialize_cmd_type_maps();
    void initialize_output_type_maps();
    void initialize_knife_maps();
    void initialize_weapon_name_maps();
    void initialize_weapon_type_maps();

    std::vector<std::string> split(const std::string& s) const;
    void serialize_buy(std::string& srlzd_cmd, const Command& cmd) const;
    void serialize_ammo(std::string& srlzd_cmd, const Command& cmd) const;
    void serialize_equipment(std::string& srlzd_output, const Output& output) const;
    Command deserialize_buy(const std::vector<std::string>& srlzd_cmd_tkns) const;
    Command deserialize_ammo(const std::vector<std::string>& srlzd_cmd_tkns) const;
    Output deserialize_equipment(const std::vector<std::string>& slrzd_output_tkns) const;
public:
    /*
     * Constructor initializes maps
     * */
    TextSerializer();

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
