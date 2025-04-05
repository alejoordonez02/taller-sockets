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
    char srlzd_cmd[] ={
        0x02,   // buy
        0x04    // awp
    };
    Command expected(Type::BUY, WeaponName::AWP);

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
    char srlzd_cmd[] = {
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

// Command::Command(
//     int money,
//     bool knife,
//     WeaponName primary,
//     WeaponName secondary,
//     int primary_ammo,
//     int secondary_ammo) :
//     money(money),
//     knife(knife),
//     primary(primary),
//     secondary(secondary),
//     primary_ammo(primary_ammo),
//     secondary_ammo(secondary_ammo) {}
    // case Type::EQUIPMENT:
    //     srlzd
void test_binary_srlz_cmd_equipment() {
    Type command_type = Type::EQUIPMENT;
    int money = 500;
    bool knife = true;
    WeaponName primary = WeaponName::NONE;
    WeaponName secondary = WeaponName::GLOCK;
    int primary_ammo = 0;
    int secondary_ammo = 30;

    Command cmd(
        command_type,
        money,
        knife,
        primary,
        secondary,
        primary_ammo,
        secondary_ammo);

    std::vector<uint8_t> expected_srlzd_cmd = {
        0x07,
        0x01, 0xf4,
        0x01,
        0x00,
        0x00, 0x00,
        0x01,
        0x00, 0x1e
    };

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    std::vector<uint8_t> srlzd_cmd;
    int ret = prtcl->srlz_cmd(srlzd_cmd, cmd);

    assert(ret == 0);
    assert(srlzd_cmd == expected_srlzd_cmd);

    std::cout << "passed test_binary_srlz_cmd_equipment()!\n";
}

void test_binary_dsrlz_cmd_equipment() {
    Type command_type = Type::EQUIPMENT;
    int money = 500;
    bool knife = true;
    WeaponName primary = WeaponName::NONE;
    WeaponName secondary = WeaponName::GLOCK;
    int primary_ammo = 0;
    int secondary_ammo = 30;

    uint8_t srlzd_cmd[] = {
        0x07,
        0x01, 0xf4,
        0x01,
        0x00,
        0x00, 0x00,
        0x01,
        0x00, 0x1e
    };

    Command expected_cmd(
        command_type,
        money,
        knife,
        primary,
        secondary,
        primary_ammo,
        secondary_ammo);

    auto prtcl = Protocol::create(ProtocolType::BINARY);

    Command dsrlzd_cmd;
    int ret = prtcl->dsrlz_cmd(dsrlzd_cmd, reinterpret_cast<const char *>(srlzd_cmd));

    assert(ret == 0);
    assert(dsrlzd_cmd == expected_cmd);

    std::cout << "passed test_binary_dsrlz_cmd_equipment()!\n";
}

int main() {
    test_binary_srlz_cmd_buy();
    test_binary_srlz_cmd_ammo();
    test_binary_dsrlz_cmd_buy();
    test_binary_dsrlz_cmd_ammo();
    test_binary_srlz_cmd_equipment();
    test_binary_dsrlz_cmd_equipment();

    return 0;
}