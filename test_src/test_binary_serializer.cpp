#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../common_src/common_binary_serializer.h"
#include "../common_src/common_command.h"

void test00_serialize_buy_command_returns_expected_srl() {
    BinarySerializer serializer;
    Command cmd("buy ak-47");

    std::vector<uint8_t> expected_srlzd = {0x02, 0x02};

    std::vector<uint8_t> srlzd = serializer.serialize(cmd);

    assert(srlzd == expected_srlzd);

    std::cout << "Passed 00!\n";
}

void test01_serialize_ammo_command_returns_expected_srl() {
    BinarySerializer serializer;
    Command cmd("ammo glock 10000");

    std::vector<uint8_t> expected_srlzd = {0x03, 0x02, 0x27, 0x10};

    std::vector<uint8_t> srlzd = serializer.serialize(cmd);

    assert(srlzd == expected_srlzd);

    std::cout << "Passed 01!\n";
}

void test02_deserialize_buy_returns_expected_cmd() {
    BinarySerializer serializer;
    Command expected_cmd("buy awp");

    std::vector<uint8_t> srlzd_cmd = {0x02, 0x04};

    Command cmd = serializer.deserialize_command(srlzd_cmd);

    assert(cmd == expected_cmd);

    std::cout << "Passed 02!\n";
}

void test03_deserialize_ammo_returns_expected_cmd() {
    BinarySerializer serializer;
    Command expected_cmd("ammo m3 10000");

    std::vector<uint8_t> srlzd_cmd = {0x03, 0x01, 0x27, 0x10};

    Command cmd = serializer.deserialize_command(srlzd_cmd);

    assert(cmd == expected_cmd);

    std::cout << "Passed 03!\n";
}

void test04_serialize_equipment_output_returns_expected_srl() {
    BinarySerializer serializer;
    Output output(OutputType::EQUIPMENT, 500, true, WeaponName::NONE, 0, WeaponName::GLOCK, 30);

    std::vector<uint8_t> expected_srl = {0x07, 0x01, 0xf4, 0x01, 0x00,
                                         0x00, 0x00, 0x01, 0x00, 0x1e};

    std::vector<uint8_t> srl = serializer.serialize(output);

    assert(srl == expected_srl);

    std::cout << "Passed 04!\n";
}

void test05_deserialize_equipment_output_returns_expected_output() {
    BinarySerializer serializer;
    Output expected_output(OutputType::EQUIPMENT, 500, true, WeaponName::NONE, 0, WeaponName::GLOCK,
                           30);

    std::vector<uint8_t> srlzd_output = {0x07, 0x01, 0xf4, 0x01, 0x00,
                                         0x00, 0x00, 0x01, 0x00, 0x1e};

    Output output = serializer.deserialize_output(srlzd_output);

    assert(output == expected_output);

    std::cout << "Passed 05!\n";
}

int main() {
    test00_serialize_buy_command_returns_expected_srl();
    test01_serialize_ammo_command_returns_expected_srl();
    test02_deserialize_buy_returns_expected_cmd();
    test03_deserialize_ammo_returns_expected_cmd();
    test04_serialize_equipment_output_returns_expected_srl();
    test05_deserialize_equipment_output_returns_expected_output();

    return 0;
}
