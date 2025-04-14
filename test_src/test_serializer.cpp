#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../common_src/common_binary_serializer.h"
#include "../common_src/common_serializer.h"
#include "../common_src/common_text_serializer.h"

void test00_serialize_username_returns_expected_srl() {
    std::string username = "mate";
    std::vector<uint8_t> expected_srl = {0x01, 0x00, 0x04, 0x6d, 0x61, 0x74, 0x65};

    std::vector<uint8_t> srl = Serializer::serialize_username(username);

    assert(srl == expected_srl);

    std::cout << "Passed 00!\n";
}

void test01_serialize_protocol_type_binary_returns_expected_srl() {
    ProtocolType type = ProtocolType::BINARY;
    std::vector<uint8_t> expected_srl = {0x06, 0x07};

    std::vector<uint8_t> srl = Serializer::serialize_protocol_type(type);

    assert(srl == expected_srl);

    std::cout << "Passed 01!\n";
}

void test02_serialize_protocol_type_text_returns_expected_srl() {
    ProtocolType type = ProtocolType::TEXT;
    std::vector<uint8_t> expected_srl = {0x06, 0x08};

    std::vector<uint8_t> srl = Serializer::serialize_protocol_type(type);

    assert(srl == expected_srl);

    std::cout << "Passed 02!\n";
}

void test03_deserialize_username_returns_expected_username() {
    std::vector<uint8_t> srl = {0x01, 0x00, 0x04, 0x6d, 0x61, 0x74, 0x65};
    std::string expected_dsrl = "mate";

    std::string dsrl = Serializer::deserialize_username(srl);

    assert(dsrl == expected_dsrl);

    std::cout << "Passed 03!\n";
}

void test04_deserialize_binary_protocol_type_returns_binary_type() {
    std::vector<uint8_t> srl = {0x06, 0x07};
    ProtocolType expected_dsrl = ProtocolType::BINARY;

    ProtocolType dsrl = Serializer::deserialize_protocol_type(srl);

    assert(dsrl == expected_dsrl);

    std::cout << "Passed 04!\n";
}

void test05_deserialize_text_protocol_type_returns_text_type() {
    std::vector<uint8_t> srl = {0x06, 0x08};
    ProtocolType expected_dsrl = ProtocolType::TEXT;

    ProtocolType dsrl = Serializer::deserialize_protocol_type(srl);

    assert(dsrl == expected_dsrl);

    std::cout << "Passed 05!\n";
}

int main() {
    test00_serialize_username_returns_expected_srl();
    test01_serialize_protocol_type_binary_returns_expected_srl();
    test02_serialize_protocol_type_text_returns_expected_srl();
    test03_deserialize_username_returns_expected_username();
    test04_deserialize_binary_protocol_type_returns_binary_type();
    test05_deserialize_text_protocol_type_returns_text_type();

    return 0;
}
