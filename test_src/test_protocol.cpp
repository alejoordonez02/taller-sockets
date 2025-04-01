#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "../common_src/common_protocol.h"
#include "../common_src/common_binary_protocol.h"
#include "../common_src/common_text_protocol.h"
#include "../common_src/common_command.h"

void test_srlz_username() {
    std::string username = "abcd";

    std::vector<uint8_t> expected = {
        0x01,
        0x00, 0x04,
        'a', 'b', 'c', 'd'
    };

    std::vector<uint8_t> srlzd_username;
    int ret = Protocol::srlz_username(srlzd_username, username);

    assert(ret == 0);
    assert(srlzd_username == expected);

    std::cout << "passed test_srlz_username()!\n";
}

void test_dsrlz_prtcl_t() {
    ProtocolType expected1 = ProtocolType::BINARY;
    ProtocolType expected2 = ProtocolType::TEXT;

    char msg1[2] = {
        0x06,
        0x07
    };

    char msg2[2] = {
        0x06,
        0x08
    };

    ProtocolType prtcl_t1;
    ProtocolType prtcl_t2;

    int ret1 = Protocol::dsrlz_prtcl_t(&prtcl_t1, msg1);
    int ret2 = Protocol::dsrlz_prtcl_t(&prtcl_t2, msg2);

    assert(ret1 == 0);
    assert(ret2 == 0);
    assert(prtcl_t1 == expected1);
    assert(prtcl_t2 == expected2);

    std::cout << "passed test_dsrlz_prtcl_t()!\n";
}

void test_create() {
    ProtocolType binary_type = ProtocolType::BINARY;
    ProtocolType text_type = ProtocolType::TEXT;
    
    auto binary_protocol = Protocol::create(binary_type);
    auto text_protocol = Protocol::create(text_type);
    
    assert(binary_protocol != nullptr);
    assert(text_protocol != nullptr);

    std::cout << "passed test_create_protocol()!\n";
}

void test_dsrlz_username() {
    char srlzd_username[] = {
        0x01,
        0x00, 0x04,
        'a', 'b', 'c', 'd'
    };

    std::string expected = "abcd";

    std::string username;
    int ret = Protocol::dsrlz_username(username, srlzd_username);

    assert(ret == 0);
    assert(username == expected);

    std::cout << "passed test_dsrlz_username()!\n";
}

void test_srlz_prtcl_t() {
    std::string prtcl_t1 = "binary";
    std::string prtcl_t2 = "text";

    std::vector<uint8_t> expected1 = {0x06, 0x07};
    std::vector<uint8_t> expected2 = {0x06, 0x08};

    std::vector<uint8_t> srlzd_prtcl_t1;
    std::vector<uint8_t> srlzd_prtcl_t2;

    int ret1 = Protocol::srlz_prtcl_t(srlzd_prtcl_t1, prtcl_t1);
    int ret2 = Protocol::srlz_prtcl_t(srlzd_prtcl_t2, prtcl_t2);

    assert(ret1 == 0);
    assert(ret2 == 0);
    assert(srlzd_prtcl_t1 == expected1);
    assert(srlzd_prtcl_t2 == expected2);

    std::cout << "passed test_srlz_prtcl_t()!\n";
}

void test_binary_srlz_cmd_buy() {
    Command cmd("buy awp");

    std::vector<uint8_t> expected = {0x02, 0x04};

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    std::vector<uint8_t> srlzd_cmd;
    int ret = prtcl->srlz_cmd(srlzd_cmd, cmd);

    assert(ret == 0);
    assert(srlzd_cmd == expected);

    std::cout << "passed test_binary_srlz_cmd_buy()!\n";
}

void test_binary_srlz_cmd_ammo() {
    Command cmd("ammo ak-47 15");
    std::vector<uint8_t> expected = {
        0x03,
        0x01,
        0x00, 0x0f
    };

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    std::vector<uint8_t> srlzd_cmd;
    int ret = prtcl->srlz_cmd(srlzd_cmd, cmd);

    assert(ret == 0);
    assert(srlzd_cmd == expected);

    std::cout << "passed test_binary_srlz_cmd_ammo()!\n";
}

void test_binary_dsrlz_cmd_buy() {
    // 
}

void test_binary_dsrlz_cmd_ammo() {
    // 
}

int main() {
    test_srlz_username();
    test_dsrlz_prtcl_t();
    test_create();
    test_dsrlz_username();
    test_srlz_prtcl_t();
    test_binary_srlz_cmd_buy();
    test_binary_srlz_cmd_ammo();

    return 0;
}