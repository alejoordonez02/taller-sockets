#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

#include "../common_src/common_protocol.h"
#include "../common_src/common_binary_protocol.h"
#include "../common_src/common_command.h"

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
    std::vector<uint8_t> srlzd_cmd ={
        0x02,   // buy
        0x04    // awp
    };
    Command expected(Type::BUY, Weapon::AWP);

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    Command dsrlzd_cmd;
    int ret = prtcl->dsrlz_cmd(dsrlzd_cmd, srlzd_cmd);

    assert(ret == 0);
    assert(dsrlzd_cmd.get_t() == expected.get_t());
    assert(dsrlzd_cmd.get_wpn() == expected.get_wpn());
    // assert(dsrlzd_cmd == expected);

    std::cout << "passed test_binary_dsrlz_cmd_buy()!\n";
}

void test_binary_dsrlz_cmd_ammo() {
    std::vector<uint8_t> srlzd_cmd = {
        0x03,       // ammo
        0x01,       // ak-47
        0x00, 0x0f  // 15
    };
    Command expected(Type::AMMO, WeaponType::PRIMARY, 15);

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    Command dsrlzd_cmd;
    int ret = prtcl->dsrlz_cmd(dsrlzd_cmd, srlzd_cmd);

    assert(ret == 0);
    assert(dsrlzd_cmd.get_t() == expected.get_t());
    assert(dsrlzd_cmd.get_wpn_t() == expected.get_wpn_t());
    assert(dsrlzd_cmd.get_count() == expected.get_count());
    // assert(dsrlzd_cmd == expected);
    std::cout << "passed test_binary_dsrlz_cmd_ammo()!\n";
}

int main() {
    test_srlz_username();
    test_dsrlz_prtcl_t();
    test_create();
    test_dsrlz_username();
    test_srlz_prtcl_t();
    test_binary_srlz_cmd_buy();
    test_binary_srlz_cmd_ammo();
    test_binary_dsrlz_cmd_buy();
    test_binary_dsrlz_cmd_ammo();

    return 0;
}