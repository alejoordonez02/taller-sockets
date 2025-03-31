#ifndef BINARY_PROTOCOL_H
#define BINARY_PROTOCOL_H

#include <string>
#include <vector>

#include "common_protocol.h"

class BinaryProtocol : public Protocol {
private:
    std::string srlz_buy(std::string &cmd);
    std::string srlz_ammo(std::string &cmd);

public:
    std::string srlz(std::string &cmd) override;
};

#endif
