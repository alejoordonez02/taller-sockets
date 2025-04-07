#include <cassert>
#include <iostream>

#include "../common_src/common_protocol.h"
#include "../common_src/common_binary_protocol.h"
#include "../common_src/common_text_protocol.h"

void test00_create_server_binary_returns_binary_instance() {
    Protocol* protocol;
    int ret = Protocol::create(protocol, ProtocolType::BINARY, "1234");

    assert(!ret);
    assert(typeid(*protocol) == typeid(BinaryProtocol));

    delete protocol;
    std::cout << "Passed 00!\n";
}

void test01_create_server_text_returns_text_instance() {
    Protocol* protocol;
    int ret = Protocol::create(protocol, ProtocolType::TEXT, "1234");

    assert(!ret);
    assert(typeid(*protocol) == typeid(TextProtocol));

    delete protocol;
    std::cout << "Passed 01!\n";
}

void test02_create_client_binary_returns_binary_instance() {
    Socket server_mock = Socket("1234");

    Protocol* protocol;
    int ret = Protocol::create(protocol, ProtocolType::BINARY, "localhost", "1234");

    assert(!ret);
    assert(typeid(*protocol) == typeid(BinaryProtocol));

    delete protocol;
    std::cout << "Passed 02!\n";
}

void test03_create_client_text_returns_text_instance() {
    Socket server_mock = Socket("1234");

    Protocol* protocol;
    int ret = Protocol::create(protocol, ProtocolType::TEXT, "localhost", "1234");

    assert(!ret);
    assert(typeid(*protocol) == typeid(TextProtocol));

    delete protocol;
    std::cout << "Passed 03!\n";
}

int main() {
    test00_create_server_binary_returns_binary_instance();
    test01_create_server_text_returns_text_instance();
    test02_create_client_binary_returns_binary_instance();
    test03_create_client_text_returns_text_instance();

    return 0;
}