#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "../common_src/common_serializer.h"

void test00_serialize_username_returns_expected_srl() {
    std::string username = "mate";
    std::vector<uint8_t> expected_srl = {
        0x01,
        0x00, 0x04,
        0x6d, 0x61, 0x74, 0x65
    };

    std::vector<uint8_t> srl;
    int ret = Serializer::serialize_username(srl, username);

    assert(!ret);
    assert(srl == expected_srl);

    std::cout << "Passed 00!\n";
}

void test01_serialize_protocol_type_binary_returns_expected_srl() {
    ProtocolType type = ProtocolType::BINARY;
    std::vector<uint8_t> expected_srl = {
        0x06,
        0x07
    };

    std::vector<uint8_t> srl;
    int ret = Serializer::serialize_protocol_type(srl, type);

    assert(!ret);
    assert(srl == expected_srl);

    std::cout << "Passed 01!\n";
}

void test02_serialize_protocol_type_text_returns_expected_srl() {
    ProtocolType type = ProtocolType::TEXT;
    std::vector<uint8_t> expected_srl = {
        0x06,
        0x08
    };

    std::vector<uint8_t> srl;
    int ret = Serializer::serialize_protocol_type(srl, type);

    assert(!ret);
    assert(srl == expected_srl);

    std::cout << "Passed 02!\n";
}

int main() {
    test00_serialize_username_returns_expected_srl();
    test01_serialize_protocol_type_binary_returns_expected_srl();
    test02_serialize_protocol_type_text_returns_expected_srl();

    return 0;
}