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

    std::vector<uint8_t> srlzd;
    int ret = serializer.serialize(srlzd, cmd);

    assert(!ret);
    assert(srlzd == expected_srlzd);

    std::cout << "Passed 00!\n";
}

void test01_serialize_ammo_command_returns_expected_srl() {
    BinarySerializer serializer;
    Command cmd("ammo glock 10000");

    std::vector<uint8_t> expected_srlzd = {0x03, 0x02, 0x27, 0x10};

    std::vector<uint8_t> srlzd;
    int ret = serializer.serialize(srlzd, cmd);

    assert(!ret);
    assert(srlzd == expected_srlzd);

    std::cout << "Passed 01!\n";
}

int main() {
    test00_serialize_buy_command_returns_expected_srl();
    test01_serialize_ammo_command_returns_expected_srl();

    return 0;
}
