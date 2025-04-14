#include "common_text_serializer.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "common_command.h"
#include "common_output.h"
#include "common_text_serials.h"
#include "common_tokenizer.h"

/*
 * Mapeo inverso
 * */
template <typename K, typename V>
std::map<V, K> get_inverse_map(const std::map<K, V>& map) {
    std::map<V, K> inverse_map;
    for (const auto& [key, value]: map) {
        inverse_map[value] = key;
    }

    return inverse_map;
}

/*
 * Consturctor helpers
 * */
void TextSerializer::initialize_cmd_type_maps() {
    srl_to_cmd_type = {{TextConstant::SRL_BUY, CommandType::BUY},
                       {TextConstant::SRL_AMMO_PRIMARY, CommandType::AMMO},
                       {TextConstant::SRL_AMMO_SECONDARY, CommandType::AMMO}};
}

void TextSerializer::initialize_output_type_maps() {
    output_type_to_srl = {{OutputType::EQUIPMENT, TextConstant::SRL_EQUIPMENT}};

    srl_to_output_type = get_inverse_map(output_type_to_srl);
}

void TextSerializer::initialize_knife_maps() {
    knife_to_srl = {{true, TextConstant::SRL_KNIFE_EQUIPPED},
                    {false, TextConstant::SRL_KNIFE_NOT_EQUIPPED}};

    srl_to_knife = get_inverse_map(knife_to_srl);
}

void TextSerializer::initialize_weapon_name_maps() {
    weapon_name_to_srl = {{WeaponName::NONE, TextConstant::SRL_NONE},
                          {WeaponName::GLOCK, TextConstant::SRL_GLOCK},
                          {WeaponName::AK47, TextConstant::SRL_AK47},
                          {WeaponName::M3, TextConstant::SRL_M3},
                          {WeaponName::AWP, TextConstant::SRL_AWP}};

    srl_to_weapon_name = get_inverse_map(weapon_name_to_srl);
}

void TextSerializer::initialize_weapon_type_maps() {
    weapon_type_to_srl = {{WeaponType::PRIMARY, TextConstant::SRL_AMMO_PRIMARY},
                          {WeaponType::SECONDARY, TextConstant::SRL_AMMO_SECONDARY}};

    srl_to_weapon_type = get_inverse_map(weapon_type_to_srl);
}

/*
 * Constructor
 * */
TextSerializer::TextSerializer() {
    initialize_cmd_type_maps();
    initialize_output_type_maps();
    initialize_knife_maps();
    initialize_weapon_name_maps();
    initialize_weapon_type_maps();
}

/*
 * Split
 * */
std::vector<std::string> TextSerializer::split(const std::string& s) const {
    std::vector<std::string> tkns;
    const std::string delims = TextConstant::DELIMITERS;
    size_t start = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        if (delims.find(s[i]) != std::string::npos) {
            if (i > start)
                tkns.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }

    if (start < s.size())
        tkns.push_back(s.substr(start));

    return tkns;
}

/*
 * Commands
 * */
void TextSerializer::serialize_buy(std::string& srlzd_cmd, const Command& cmd) const {
    std::string srlzd_weapon_name = weapon_name_to_srl.at(cmd.get_weapon_name());
    srlzd_cmd.append(TextConstant::SRL_BUY);
    srlzd_cmd.append(":");
    srlzd_cmd.append(srlzd_weapon_name);
}

void TextSerializer::serialize_ammo(std::string& srlzd_cmd, const Command& cmd) const {
    std::string srlzd_weapon_type = weapon_type_to_srl.at(cmd.get_weapon_type());
    std::string srlzd_count = std::to_string(cmd.get_count());

    srlzd_cmd.append(srlzd_weapon_type);
    srlzd_cmd.append(":");
    srlzd_cmd.append(srlzd_count);
}

std::string TextSerializer::serialize(const Command& cmd) const {
    std::string srlzd_cmd;

    switch (cmd.get_type()) {
        case CommandType::BUY:
            serialize_buy(srlzd_cmd, cmd);
            break;
        case CommandType::AMMO:
            serialize_ammo(srlzd_cmd, cmd);
            break;
        default:
            srlzd_cmd.clear();
            break;
    }

    srlzd_cmd.append("\n");

    return srlzd_cmd;
}

Command TextSerializer::deserialize_buy(const std::vector<std::string>& srlzd_cmd_tkns) const {
    WeaponName dsrlzd_weapon_name = srl_to_weapon_name.at(srlzd_cmd_tkns[1]);
    return Command(CommandType::BUY, dsrlzd_weapon_name);
}

Command TextSerializer::deserialize_ammo(const std::vector<std::string>& srlzd_cmd_tkns) const {
    WeaponType dsrlzd_weapon_type = srl_to_weapon_type.at(srlzd_cmd_tkns[0]);
    int dsrlzd_count = std::stoi(srlzd_cmd_tkns[1]);
    return Command(CommandType::AMMO, dsrlzd_weapon_type, dsrlzd_count);
}

Command TextSerializer::deserialize_command(const std::string& srlzd_cmd) const {
    std::vector<std::string> tkns = split(srlzd_cmd);
    CommandType dsrlzd_command_type = srl_to_cmd_type.at(tkns[0]);

    switch (dsrlzd_command_type) {
        case CommandType::BUY:
            return deserialize_buy(tkns);
        case CommandType::AMMO:
            return deserialize_ammo(tkns);
        default:
            return Command();
    }
}

/*
 * Outputs
 * */
void TextSerializer::serialize_equipment(std::string& srlzd_output, const Output& output) const {
    std::string srlzd_money = std::to_string(output.get_money());

    std::string srlzd_knife = knife_to_srl.at(output.get_knife());

    std::string srlzd_primary = weapon_name_to_srl.at(output.get_primary());
    std::string srlzd_primary_ammo = std::to_string(output.get_primary_ammo());

    std::string srlzd_secondary = weapon_name_to_srl.at(output.get_secondary());
    std::string srlzd_secondary_ammo = std::to_string(output.get_secondary_ammo());

    srlzd_output.append(TextConstant::SRL_MONEY);
    srlzd_output.append(":");
    srlzd_output.append(srlzd_money);
    srlzd_output.append("\n");
    srlzd_output.append(TextConstant::SRL_KNIFE);
    srlzd_output.append(":");
    srlzd_output.append(srlzd_knife);
    srlzd_output.append("\n");
    srlzd_output.append(TextConstant::SRL_PRIMARY);
    srlzd_output.append(":");
    srlzd_output.append(srlzd_primary);
    srlzd_output.append(",");
    srlzd_output.append(srlzd_primary_ammo);
    srlzd_output.append("\n");
    srlzd_output.append(TextConstant::SRL_SECONDARY);
    srlzd_output.append(":");
    srlzd_output.append(srlzd_secondary);
    srlzd_output.append(",");
    srlzd_output.append(srlzd_secondary_ammo);
}

std::string TextSerializer::serialize(const Output& output) const {
    std::string srlzd_output;

    switch (output.get_type()) {
        case OutputType::EQUIPMENT:
            serialize_equipment(srlzd_output, output);
            break;
        default:
            srlzd_output.clear();
            break;
    }

    srlzd_output.append("\n");

    return srlzd_output;
}

Output TextSerializer::deserialize_equipment(
        const std::vector<std::string>& slrzd_output_tkns) const {
    int dsrlzd_money = std::stoi(slrzd_output_tkns[1]);
    bool dsrlzd_knife = srl_to_knife.at(slrzd_output_tkns[3]);
    WeaponName dsrlzd_primary = srl_to_weapon_name.at(slrzd_output_tkns[5]);
    int dsrlzd_primary_ammo = std::stoi(slrzd_output_tkns[6]);
    WeaponName dsrlzd_secondary = srl_to_weapon_name.at(slrzd_output_tkns[8]);
    int dsrlzd_secondary_ammo = std::stoi(slrzd_output_tkns[9]);

    return Output(OutputType::EQUIPMENT, dsrlzd_money, dsrlzd_knife, dsrlzd_primary,
                  dsrlzd_primary_ammo, dsrlzd_secondary, dsrlzd_secondary_ammo);
}

Output TextSerializer::deserialize_output(const std::string& srlzd_output) const {
    std::vector<std::string> tkns = split(srlzd_output);
    OutputType dsrlzd_output_type = srl_to_output_type.at(tkns[0]);

    switch (dsrlzd_output_type) {
        case OutputType::EQUIPMENT:
            return deserialize_equipment(tkns);
        default:
            return Output();
    }
}
