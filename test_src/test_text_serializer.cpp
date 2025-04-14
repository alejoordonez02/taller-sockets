#include <cassert>
#include <iostream>

#include "../common_src/common_command.h"
#include "../common_src/common_output.h"
#include "../common_src/common_text_serializer.h"

void test00_serialize_cmd_buy_returns_expected_srl() {
    TextSerializer serializer;
    Command cmd("buy awp");

    std::string expected_srl = "buy.weapon:awp\n";

    std::string srl = serializer.serialize(cmd);

    assert(srl == expected_srl);

    std::cout << "Passed 00!\n";
}

void test01_serialize_cmd_ammo_primary_returns_expected_srl() {
    TextSerializer serializer;
    Command cmd("ammo ak-47 30");

    std::string expected_srl = "buy.ammo.primary:30\n";

    std::string srl = serializer.serialize(cmd);

    assert(srl == expected_srl);

    std::cout << "Passed 01!\n";
}

void test02_serialize_cmd_ammo_secondary_returns_expected_srl() {
    TextSerializer serializer;
    Command cmd("ammo glock 30");

    std::string expected_srl = "buy.ammo.secondary:30\n";

    std::string srl = serializer.serialize(cmd);

    assert(srl == expected_srl);

    std::cout << "Passed 02!\n";
}

void test03_serialize_equipment_returns_expected_srl() {
    TextSerializer serializer;
    Output output(OutputType::EQUIPMENT, 500, true, WeaponName::NONE, 0, WeaponName::GLOCK, 30);

    std::string expected_srl = "equipment.money:500\nequipment.knife:true\nequipment.primary:none,"
                               "0\nequipment.secondary:glock,30\n";

    std::string srl = serializer.serialize(output);

    assert(srl == expected_srl);

    std::cout << "Passed 03!\n";
}

void test04_deserialize_equipment_returns_expected_output() {
    TextSerializer serializer;
    std::string srl = "equipment.money:500\nequipment.knife:true\nequipment.primary:none,"
                      "0\nequipment.secondary:glock,30\n";

    Output expected_output(OutputType::EQUIPMENT, 500, true, WeaponName::NONE, 0, WeaponName::GLOCK,
                           30);

    Output output = serializer.deserialize_output(srl);

    assert(output == expected_output);

    std::cout << "Passed 04!\n";
}

int main() {
    test00_serialize_cmd_buy_returns_expected_srl();
    test01_serialize_cmd_ammo_primary_returns_expected_srl();
    test02_serialize_cmd_ammo_secondary_returns_expected_srl();
    test03_serialize_equipment_returns_expected_srl();
    test04_deserialize_equipment_returns_expected_output();

    return 0;
}