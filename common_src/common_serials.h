#ifndef SERIALS_H
#define SERIALS_H

#include <cstdint>

namespace SerialConstant {
constexpr uint8_t SRL_USERNAME = 0x01;
constexpr uint8_t SRL_PROTOCOL_TYPE = 0x06;
constexpr uint8_t SRL_BINARY = 0x07;
constexpr uint8_t SRL_TEXT = 0x08;
}  // namespace SerialConstant

#endif
