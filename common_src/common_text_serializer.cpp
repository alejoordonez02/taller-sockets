#include "common_text_serializer.h"

#include <map>
#include <string>
#include <vector>

#include "common_command.h"
#include "common_output.h"
#include "common_text_serials.h"
#include "common_tokenizer.h"

/*
 * Commands
 * */
void TextSerializer::serialize_buy(std::string& srlzd_cmd, const Command& cmd) const {
    std::string srlzd_weapon_name = TextConstant::WEAPON_NAME_TO_SRL.at(cmd.get_weapon_name());
    srlzd_cmd.append(TextConstant::SRL_BUY);
    srlzd_cmd.append(":");
    srlzd_cmd.append(srlzd_weapon_name);
}

void TextSerializer::serialize_ammo(std::string& srlzd_cmd, const Command& cmd) const {
    std::string srlzd_weapon_type = TextConstant::WEAPON_TYPE_TO_SRL.at(cmd.get_weapon_type());
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
    WeaponName dsrlzd_weapon_name = TextConstant::SRL_TO_WEAPON_NAME.at(srlzd_cmd_tkns[1]);
    return Command(CommandType::BUY, dsrlzd_weapon_name);
}

Command TextSerializer::deserialize_ammo(const std::vector<std::string>& srlzd_cmd_tkns) const {
    WeaponType dsrlzd_weapon_type = TextConstant::SRL_TO_WEAPON_TYPE.at(srlzd_cmd_tkns[0]);
    int dsrlzd_count = std::stoi(srlzd_cmd_tkns[1]);
    return Command(CommandType::AMMO, dsrlzd_weapon_type, dsrlzd_count);
}

Command TextSerializer::deserialize_command(const std::string& srlzd_cmd) const {
    std::vector<std::string> tkns = Tokenizer::tknz(srlzd_cmd, TextConstant::DELIMITERS);
    CommandType dsrlzd_command_type = TextConstant::SRL_TO_CMD_TYPE.at(tkns[0]);

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

    std::string srlzd_knife = TextConstant::KNIFE_TO_SRL.at(output.get_knife());

    std::string srlzd_primary = TextConstant::WEAPON_NAME_TO_SRL.at(output.get_primary());
    std::string srlzd_primary_ammo = std::to_string(output.get_primary_ammo());

    std::string srlzd_secondary = TextConstant::WEAPON_NAME_TO_SRL.at(output.get_secondary());
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
    bool dsrlzd_knife = TextConstant::SRL_TO_KNIFE.at(slrzd_output_tkns[3]);
    WeaponName dsrlzd_primary = TextConstant::SRL_TO_WEAPON_NAME.at(slrzd_output_tkns[5]);
    int dsrlzd_primary_ammo = std::stoi(slrzd_output_tkns[6]);
    WeaponName dsrlzd_secondary = TextConstant::SRL_TO_WEAPON_NAME.at(slrzd_output_tkns[8]);
    int dsrlzd_secondary_ammo = std::stoi(slrzd_output_tkns[9]);

    return Output(OutputType::EQUIPMENT, dsrlzd_money, dsrlzd_knife, dsrlzd_primary,
                  dsrlzd_primary_ammo, dsrlzd_secondary, dsrlzd_secondary_ammo);
}

Output TextSerializer::deserialize_output(const std::string& srlzd_output) const {
    std::vector<std::string> tkns = Tokenizer::tknz(srlzd_output, TextConstant::DELIMITERS);
    OutputType dsrlzd_output_type = TextConstant::SRL_TO_OUTPUT_TYPE.at(tkns[0]);

    switch (dsrlzd_output_type) {
        case OutputType::EQUIPMENT:
            return deserialize_equipment(tkns);
        default:
            return Output();
    }
}
